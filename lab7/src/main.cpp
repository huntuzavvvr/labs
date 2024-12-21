#include <iostream>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <queue>
#include <chrono>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <map>
#include "NPC.hpp"
#include "Elf.hpp"
#include "Robber.hpp"
#include "Walkingknight.hpp"
#include "NPCFactory.hpp"
#include "ElfFactory.hpp"
#include "RobberFactory.hpp"
#include "WalkingknightFactory.hpp"

bool gameRunning = true;
std::shared_mutex mtx;
std::mutex coutMutex;

std::map<std::string, int> MOVEMENT_DISTANCES = {
    {"Elf", 10},
    {"Robber", 10},
    {"Walkingknight", 30},
};

std::map<std::string, int> KILLING_RANGES = {
    {"Elf", 50},
    {"Robber", 10},
    {"Walkingknight", 10},
};

void movementThread(std::vector<std::unique_ptr<NPC>>& npcs, std::queue<std::pair<NPC*, NPC*>>& battleQueue) {
    while (gameRunning) {
        std::shared_lock<std::shared_mutex> lock(mtx);
        for (auto& npc : npcs) {
            if (!npc->isAlive()) continue;
            int moveX = rand() % (2 * MOVEMENT_DISTANCES[npc->getType()]) - MOVEMENT_DISTANCES[npc->getType()];
            int moveY = rand() % (2 * MOVEMENT_DISTANCES[npc->getType()]) - MOVEMENT_DISTANCES[npc->getType()];
            npc->setX(npc->getX() + moveX);
            npc->setY(npc->getY() + moveY);
            npc->setX(std::max(0, std::min(100, npc->getX())));
            npc->setY(std::max(0, std::min(100, npc->getY())));
        }

        for (size_t i = 0; i < npcs.size(); ++i) {
            for (size_t j = i + 1; j < npcs.size(); ++j) {
                NPC* a = npcs[i].get();
                NPC* b = npcs[j].get();
                if (a->isAlive() && b->isAlive() && a->fight(b)) {
                    int distance = std::sqrt((a->getX() - b->getX()) * (a->getX() - b->getX()) + (a->getY() - b->getY()) * (a->getY() - b->getY()));
                    if (distance <= KILLING_RANGES[a->getType()]) {
                        std::lock_guard<std::shared_mutex> lock(mtx);
                        battleQueue.push({a, b});
                    }
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void battleThread(std::queue<std::pair<NPC*, NPC*>>& battleQueue) {
    while (gameRunning) {
        std::pair<NPC*, NPC*> battle;
        {
            std::lock_guard<std::shared_mutex> lock(mtx);
            if (!battleQueue.empty()) {
                battle = battleQueue.front();
                battleQueue.pop();
            }
        }
        if (battle.first && battle.second) {
            int attackerStrength = rand() % 6 + 1;
            int defenderStrength = rand() % 6 + 1;
            if (attackerStrength > defenderStrength) {
                battle.second->kill();
                std::lock_guard<std::mutex> coutLock(coutMutex);
                std::cout << battle.first->getName() << " убил " << battle.second->getName() << std::endl;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void renderThread(std::vector<std::unique_ptr<NPC>>& npcs) {
    while (gameRunning) {
        std::shared_lock<std::shared_mutex> lock(mtx);
        std::lock_guard<std::mutex> coutLock(coutMutex);
        std::cout << "Текущие NPC:\n";
        for (const auto& npc : npcs) {
            if (npc->isAlive()) {
                std::cout << "Тип: " << npc->getType() << ", Имя: " << npc->getName() << ", Позиция: (" << npc->getX() << ", " << npc->getY() << ")\n";
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    NPCFactory::registerFactory("Elf", new ElfFactory());
    NPCFactory::registerFactory("Robber", new RobberFactory());
    NPCFactory::registerFactory("Walkingknight", new WalkingknightFactory());

    std::vector<std::unique_ptr<NPC>> npcs;
    std::queue<std::pair<NPC*, NPC*>> battleQueue;

    for (int i = 0; i < 50; ++i) {
        std::string type = (rand() % 3 == 0) ? "Elf" : (rand() % 2 == 0) ? "Robber" : "Walkingknight";
        std::string name = "NPC" + std::to_string(i);
        int x = rand() % 100;
        int y = rand() % 100;
        npcs.push_back(NPCFactory::create(type, name, x, y));
    }

    std::thread movement(movementThread, std::ref(npcs), std::ref(battleQueue));
    std::thread battle(battleThread, std::ref(battleQueue));
    std::thread render(renderThread, std::ref(npcs));

    std::this_thread::sleep_for(std::chrono::seconds(30));
    gameRunning = false;

    movement.join();
    battle.join();
    render.join();

    std::cout << "Выжившие:\n";
    for (const auto& npc : npcs) {
        if (npc->isAlive()) {
            std::cout << "Тип: " << npc->getType() << ", Имя: " << npc->getName() << ", Позиция: (" << npc->getX() << ", " << npc->getY() << ")\n";
        }
    }

    return 0;
}
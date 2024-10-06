#ifndef ELEVEN_H
#define ELEVEN_H
#include <string>
#include <iostream>


class Eleven{
    public:
        Eleven();
        Eleven(const size_t& n, unsigned char t = 0);
        Eleven(const std::string &t);
        Eleven(const std::initializer_list<unsigned char> &t);
        Eleven(const Eleven &other);
        Eleven(Eleven&& other) noexcept;
        virtual ~Eleven() noexcept;

        Eleven& operator+=(const Eleven& other);
        Eleven& operator-=(const Eleven& other);
        Eleven& operator=(const Eleven& other);
        Eleven& operator=(Eleven&& other) noexcept;
        bool operator>(const Eleven& other) const;
        bool operator<(const Eleven& other) const;
        bool operator==(const Eleven& other) const;
        size_t get_size() const;
        unsigned char* get_data() const;
    private:
        unsigned char* data;
        size_t size;
        void delete_zero();

};
std::ostream& operator<<(std::ostream& a, const Eleven& number);

#endif
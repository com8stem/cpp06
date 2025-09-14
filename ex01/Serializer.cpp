#include "Serializer.hpp"

Data::Data(std::string name, int id) : name_(name), id_(id)
{
}

Serializer::Serializer()
{
}

Serializer::Serializer(const Serializer &)
{
}

Serializer &Serializer::operator=(const Serializer &)
{
    return *this;
}

Serializer::~Serializer()
{
}

uintptr_t Serializer::serialize(Data* ptr)
{
    return reinterpret_cast<uintptr_t>(ptr);
}

Data* Serializer::deserialize(uintptr_t raw)
{
    return reinterpret_cast<Data *>(raw);
}

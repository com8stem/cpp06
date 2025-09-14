#include "Serializer.hpp"

int main()
{
    std::string names[] = {"alpha", "bravo", "charlie"};
    int ids[] = {1, 2, 3};

    for(int i = 0; i < 3; i++)
    {
        Data d(names[i], ids[i]);
        uintptr_t ptr_uint = Serializer::serialize(&d);
        Data *d_deserialized = Serializer::deserialize(ptr_uint);

        std::cout << "name:" << d.name_ << "     " << "id:" << d.id_ << std::endl;
        std::cout << "deserialized name:" << d_deserialized->name_ << "     " << "deserialized id:" << d_deserialized->id_ << std::endl;
    }
    return 0;
}

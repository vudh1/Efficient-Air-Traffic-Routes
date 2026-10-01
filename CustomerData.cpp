#include "CustomerData.h"

#include <ctime>
#include <iomanip>

namespace
{
int currentMinutes()
{
    const std::time_t now = std::time(nullptr);
    std::tm local{};

#ifdef _WIN32
    localtime_s(&local, &now);
#else
    localtime_r(&now, &local);
#endif

    return local.tm_hour * 60 + local.tm_min;
}
}

customerData::customerData()
    : plateNumber(), name(), brand(), timeIn(0), timeOut(0), timeLength(0)
{
}

customerData::customerData(const std::string& entryName)
    : plateNumber(), name(entryName), brand(), timeIn(0), timeOut(0), timeLength(0)
{
}

void customerData::setPlate(const std::string& value)
{
    plateNumber = value;
}

void customerData::setName(const std::string& value)
{
    name = value;
}

void customerData::setBrand(const std::string& value)
{
    brand = value;
}

std::string customerData::getPlate() const
{
    return plateNumber;
}

std::string customerData::getName() const
{
    return name;
}

std::string customerData::getBrand() const
{
    return brand;
}

void customerData::getTimeIn()
{
    timeIn = currentMinutes();
    std::cout << "Time In: " << timeIn / 60 << ":" << std::setfill('0')
              << timeIn % 60 << std::setfill(' ') << '\\n';
}

void customerData::getTimeOut()
{
    timeOut = currentMinutes();
    std::cout << "Time Out: " << timeOut / 60 << ":" << std::setfill('0')
              << timeOut % 60 << std::setfill(' ') << '\\n';
}

void customerData::setTimeIn(int minutes)
{
    timeIn = minutes;
}

int customerData::getTimeLength() const
{
    // Parking that crosses midnight is still charged correctly.
    return (timeOut - timeIn + 24 * 60) % (24 * 60);
}

bool customerData::operator<(const customerData& other) const
{
    return plateNumber < other.plateNumber;
}

bool customerData::operator<=(const customerData& other) const
{
    return plateNumber <= other.plateNumber;
}

bool customerData::operator==(const customerData& other) const
{
    return plateNumber == other.plateNumber;
}

bool customerData::operator>(const customerData& other) const
{
    return plateNumber > other.plateNumber;
}

bool customerData::operator>=(const customerData& other) const
{
    return plateNumber >= other.plateNumber;
}

bool customerData::operator!=(const customerData& other) const
{
    return plateNumber != other.plateNumber;
}

bool customerData::operator<<(const customerData& other) const
{
    return name < other.name;
}

bool customerData::operator<<=(const customerData& other) const
{
    return name <= other.name;
}

bool customerData::operator*=(const customerData& other) const
{
    return name == other.name;
}

bool customerData::operator>>(const customerData& other) const
{
    return name > other.name;
}

bool customerData::operator>>=(const customerData& other) const
{
    return name >= other.name;
}

bool customerData::operator|=(const customerData& other) const
{
    return name != other.name;
}

std::ostream& operator<<(std::ostream& os, const customerData& obj)
{
    os << "[ " << std::left << std::setw(7) << obj.getPlate()
       << " | " << std::setw(22) << obj.getName()
       << " | " << std::setw(10) << obj.getBrand() << " ]";
    return os;
}

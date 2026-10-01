#ifndef CUSTOMERDATA_H_INCLUDED
#define CUSTOMERDATA_H_INCLUDED

#include <iostream>
#include <string>

class customerData
{
private:
    std::string plateNumber;
    std::string name;
    std::string brand;
    int timeIn;
    int timeOut;
    int timeLength;

public:
    customerData();
    explicit customerData(const std::string& entryName);
    ~customerData() = default;

    void setPlate(const std::string& value);
    void setName(const std::string& value);
    void setBrand(const std::string& value);

    std::string getPlate() const;
    std::string getName() const;
    std::string getBrand() const;

    void setTimeIn(int minutes);
    void getTimeIn();
    void getTimeOut();
    int getTimeLength() const;

    // Primary-key comparisons: license plate.
    bool operator<(const customerData& other) const;
    bool operator<=(const customerData& other) const;
    bool operator==(const customerData& other) const;
    bool operator>(const customerData& other) const;
    bool operator>=(const customerData& other) const;
    bool operator!=(const customerData& other) const;

    // Secondary-key comparisons: customer name.
    bool operator<<(const customerData& other) const;
    bool operator<<=(const customerData& other) const;
    bool operator*=(const customerData& other) const;
    bool operator>>(const customerData& other) const;
    bool operator>>=(const customerData& other) const;
    bool operator|=(const customerData& other) const;

    friend std::ostream& operator<<(std::ostream& os,
                                    const customerData& obj);
};

#endif

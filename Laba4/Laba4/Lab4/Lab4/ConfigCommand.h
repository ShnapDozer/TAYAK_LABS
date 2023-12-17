#pragma once
#include <string>
#include <vector>

class ConfigCommand
{
public:
    ConfigCommand();
    ConfigCommand(std::string inputVal, std::string pushdownVal, std::vector<std::string> resultStates, std::string managmentUnitVal = "S0");
    ConfigCommand(std::string inputVal, std::string pushdownVal, std::string resultState, std::string managmentUnitVal = "S0");
    
    int getType() const;
    std::string getResult() const;
    std::string getInputVal() const;
    std::string getPushdownVal() const;
    std::string getManagmentUnitVal() const;
    std::vector<std::string> getResultStates() const;
   
    std::string toString() const;

private:

    int m_type;
    std::string m_inputVal;
    std::string m_pushdownVal;
    std::string m_managmentUnitVal;
    std::vector<std::string> m_resultStates;

    void setType(std::string inputVal, std::string pushdownVal);
};


#ifndef TRANSACTION_H
#define TRANSACTION_H


#include <iostream>
#include <vector>
#include <string>
#include "sha1.hpp"


class Transaction
{
public:

    Transaction(std::string fromAdress, std::string toAdress, std::string refToTrans = "NULL")
    {
        this->setOfOperactions[0] = fromAdress;
        this->setOfOperactions[1] = toAdress;
        this->setOfOperactions[2] = refToTrans; // Ссылка на транзакцию, которая дала право голоса 
        this->nonce = setNonce();
        this->setHash(this->toInput());
    }

    Transaction(const Transaction& transaction)
    {
        this->setOfOperactions[0] = transaction.fromAdress;
        this->setOfOperactions[1] = transaction.toAdress;
        this->setOfOperactions[2] = transaction.refToTrans; // Ссылка на транзакцию, которая дала право голоса 
        this->nonce = setNonce();
        this->setHash(this->toInput());
    }

    void print()
    {
        std::cout << "\nХэш транзакции: " << this->transactionID << "\nИдентификатор транзакции: " << this->nonce << "\nНабор операций платежей: " << std::endl;
        if (!this->setOfOperactions.empty())
        {
            for (int i = 0; i < this->setOfOperactions.size(); i++)
            {
                std::cout << "--" << this->setOfOperactions[i] << std::endl;
            }
        }

    }

private:
    std::string fromAdress, toAdress, refToTrans; // Адреса: с которого переводится голос; на который переводится голос. Также ссылка на транзакцию, дающая право голоса
    std::string transactionID; // Хэш идентификатор транзакции
    int nonce; // Защита от дублирования
    std::vector <std::string> setOfOperactions{ fromAdress, toAdress, refToTrans }; // Операции

    std::string toInput() // Функция, собиирающая все данные о транзакции в строку
    {
        std::string result;
        result = std::to_string(this->nonce);
        if (!this->setOfOperactions.empty())
        {
            for (int i = 0; i < this->setOfOperactions.size(); i++)
            {
                result = result + this->setOfOperactions[i];
            }
        }

        return result;
    }

    void setHash(std::string input) // Функция хэширования данных о транзакции
    {
        SHA1 hashValue; // Пока что используется алгоритм хэширования SHA-1. В будущем возможна замена на SHA-2
        hashValue.update(input);

        this->transactionID = hashValue.final();
    }

    int setNonce() // Функция, защищающая от дублирования путём использования time() во время создания транзакции 
    {
        time_t currentTime = time(NULL);
        return (int)currentTime;
    }
};


#endif

#include "objPosArrayList.h"


objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP];
    
    listSize = 0;
    arrayCapacity = ARRAY_MAX_CAP;
}

objPosArrayList::objPosArrayList(const objPosArrayList &oList)
{
    listSize = oList.listSize;
    arrayCapacity = oList.arrayCapacity;

    for (int i = 0; i < listSize; i++)
    {
        aList[i] = oList.getElement(i);
    }
}

objPosArrayList& objPosArrayList::operator=(const objPosArrayList &oList)
{
    if (this != &oList)
    {
        delete[] aList;
        listSize = oList.getSize();
        arrayCapacity = oList.arrayCapacity;
        aList = new objPos[arrayCapacity];

        for (int i = 0; i < listSize; i++)
        {
            aList[i] = oList.getElement(i);
        }
    }
    return *this;
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if (listSize == arrayCapacity)
    {
        return;
    }

    for(int i = listSize; i > 0; i--)   
        aList[i] = aList[i - 1];  // shifting towards the tail

    aList[0] = thisPos;
    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if (listSize == arrayCapacity)
    {
        return;
    }

    aList[listSize] = thisPos;
    listSize++;
}

void objPosArrayList::removeHead()
{
    for(int i = 0; i < listSize; i++)   
        aList[i] = aList[i + 1];  // shifting towards the head

    listSize--;
}

void objPosArrayList::removeTail()
{
    listSize--;
}

objPos objPosArrayList::getHeadElement() const
{
    return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
    return aList[listSize-1];
}

objPos objPosArrayList::getElement(int index) const
{
    return aList[index];
}
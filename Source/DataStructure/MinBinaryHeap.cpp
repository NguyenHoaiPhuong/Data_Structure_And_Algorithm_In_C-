#include "MinBinaryHeap.h"

/* Children key must be bigger than or equal to parent key */

CMinBinaryHeap::CMinBinaryHeap(const long & iCapacity)
	:CBinaryHeap(iCapacity)
{
}

long CMinBinaryHeap::GetMin()
{
	_ASSERT(m_iSize > 0);
	return m_arKey[0];
}

long CMinBinaryHeap::GetMax()
{
	_ASSERT(m_iSize > 0);
	long iLevel = GetLevel(m_iSize - 1);
	const long sIdx = pow(2, iLevel) - 1;
	const long eIdx = pow(2, iLevel + 1) - 2;
	long maxKey = m_arKey[sIdx];
	for (size_t k = sIdx + 1; k < eIdx; k++)
	{
		if (m_arKey[k] > maxKey)
			maxKey = m_arKey[k];
	}
	return maxKey;
}

long CMinBinaryHeap::ExtractMin()
{
	long res = GetMin();
	Remove(res);
	return res;
}

long CMinBinaryHeap::ExtractMax()
{
	long res = GetMax();
	Remove(res);
	return res;
}

void CMinBinaryHeap::ChangeKey(const long & idx, const long & iNewKey)
{
	long curKey = m_arKey[idx];
	m_arKey[idx] = iNewKey;
	if (iNewKey > curKey)
		UpdateDown(idx);
	else if (iNewKey < curKey)
		UpdateUp(idx);
}

bool CMinBinaryHeap::Insert(const long & key)
{
	if (IsFull())
		return false;
	m_arKey[m_iSize++] = key;
	if (m_iSize > 1)
		UpdateUp(m_iSize - 1);
}

bool CMinBinaryHeap::Remove(const long & key)
{
	long idx = Find(key);
	if (idx != -1)
	{
		Swap(m_arKey[idx], m_arKey[m_iSize-1]);
		m_iSize--;
		UpdateDown(idx);
		return true;	// Remove 1 element
	}
	return false;	// No element was removed
}

void CMinBinaryHeap::UpdateUp(const long & idx)
{
	long parentIdx = GetParent(idx);
	if (m_arKey[idx] < m_arKey[parentIdx])
	{
		Swap(m_arKey[idx], m_arKey[parentIdx]);
		if (parentIdx != 0)
			UpdateUp(parentIdx);
	}
}

void CMinBinaryHeap::UpdateDown(const long & idx)
{
	long leftIdx = GetLeftChild(idx);
	long rightIdx = GetRightChild(idx);
	long minIdx = -1;
	if (leftIdx != -1 && m_arKey[leftIdx] < m_arKey[idx])
		minIdx = leftIdx;
	if (rightIdx != -1 && m_arKey[rightIdx] < m_arKey[leftIdx])
		minIdx = rightIdx;
	if (minIdx != -1)
	{
		Swap(m_arKey[idx], m_arKey[minIdx]);
		UpdateDown(minIdx);
	}
}

void CMinBinaryHeap::PrintArray()
{
	for (size_t i = 0; i < m_iSize; i++)
	{
		std::cout << m_arKey[i] << std::endl;
	}
}

void CMinBinaryHeap::PrintTree()
{
	InOrder();
	long maxLevel = GetLevel(m_iSize - 1);
	for (long k = 0; k < maxLevel; k++)
	{
		long pos = 0;
		for (long idx = pow(2, k) - 1; idx < pow(2, k + 1) - 1; idx++)
		{
			for (long i = 0; i < m_arInOrderIndex[idx] - pos; i++)
				std::cout << "\t";
			std::cout << m_arKey[idx];			
			pos = m_arInOrderIndex[idx];
		}
		std::cout << "\n";
	}
	{
		long pos = 0;
		for (long idx = pow(2, maxLevel) - 1; idx < m_iSize; idx++)
		{
			for (long i = 0; i < m_arInOrderIndex[idx] - pos; i++)
				std::cout << "\t";
			std::cout << m_arKey[idx];
			pos = m_arInOrderIndex[idx];
		}
		std::cout << "\n";
	}
}
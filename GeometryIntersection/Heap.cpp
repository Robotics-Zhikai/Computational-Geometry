#include "Heap.h"

HeapData Default;
#define ElemenTypical Default

void HeapOperate::SetMaxsizeHeap(int MaxSize)
{
	HeapOperate::MaxSize = MaxSize;
}

int HeapOperate::IsFullHeap(vector <ElemenType> HeapData)
{
	if (HeapData.size() > HeapOperate::MaxSize)
	{
		cout << "Ԫ�س��������ֵ�����ǲ�����ģ�" << endl;
		return -1;
	}
	if (HeapData.size() == HeapOperate::MaxSize)
		return 1;
	else
		return 0;
}

int HeapOperate::IsEmptyHeap(vector <ElemenType> HeapData)
{
	if (HeapData.size() == 0)
		return 1;
	else
		return 0;
}

void HeapOperate::SetMaxorMin(int MaxorMin)
{
	HeapOperate::MaxorMin = MaxorMin;
}

void HeapOperate::InsertHeapElement(vector <ElemenType> & HeapData, ElemenType Element)
{
	if (HeapOperate::IsFullHeap(HeapData) == 1)
		return;
	HeapData.push_back(Element);
	if (HeapData.size() == 1)
		return;

	if (HeapOperate::MaxorMin == 1)
	{
		for (int i = HeapData.size() - 1; i>0; i = ceil(double(i) / 2.0) - 1)
		{
			if (HeapData[i] >= HeapData[ceil(double(i) / 2.0) - 1])
			{
				ElemenType midnum = HeapData[ceil(double(i) / 2.0) - 1];
				HeapData[ceil(double(i) / 2.0) - 1] = HeapData[i];
				HeapData[i] = midnum;
			}
			else
				break;
		}
	}
	if (HeapOperate::MaxorMin == 2)
	{
		for (int i = HeapData.size() - 1; i>0; i = ceil(double(i) / 2.0) - 1)
		{
			if (HeapData[i] <= HeapData[ceil(double(i) / 2.0) - 1])
			{
				ElemenType midnum = HeapData[ceil(double(i) / 2.0) - 1];
				HeapData[ceil(double(i) / 2.0) - 1] = HeapData[i];
				HeapData[i] = midnum;
			}
			else
				break;
		}
	}
}

void HeapOperate::Change2Heap(vector <ElemenType> & RandomElement, int root, int maxormin)
//��rootΪ���ڵ㣬������Ӧ������ΪHeap,��Ȼ��������һ�������ϵ���
//���Ӷ�Ϊlogn
{
	if (RandomElement.size() <= 1)
		return;

	if (maxormin == 1)
	{
		for (int i = root; i < RandomElement.size(); )
		{
			int lchild = i * 2 + 1;
			int rchild = lchild + 1;
			if (lchild >= RandomElement.size())
				break;
			if (rchild < RandomElement.size())
			{
				if (RandomElement[lchild] > RandomElement[i] && RandomElement[rchild] > RandomElement[i])
				{
					if (RandomElement[rchild] >= RandomElement[lchild])
					{
						ElemenType mid = RandomElement[rchild];
						RandomElement[rchild] = RandomElement[i];
						RandomElement[i] = mid;
						i = rchild;
					}
					else
					{
						ElemenType mid = RandomElement[lchild];
						RandomElement[lchild] = RandomElement[i];
						RandomElement[i] = mid;
						i = lchild;
					}
				}
				else if (RandomElement[lchild] >= RandomElement[i] && RandomElement[rchild] == RandomElement[i])
				{
					ElemenType mid = RandomElement[lchild];
					RandomElement[lchild] = RandomElement[i];
					RandomElement[i] = mid;
					i = lchild;
				}
				else if (RandomElement[lchild] >= RandomElement[i] && RandomElement[rchild] < RandomElement[i])
				{
					ElemenType mid = RandomElement[lchild];
					RandomElement[lchild] = RandomElement[i];
					RandomElement[i] = mid;
					i = lchild;
				}
				else if (RandomElement[rchild] >= RandomElement[i] && RandomElement[lchild] < RandomElement[i])
				{
					ElemenType mid = RandomElement[rchild];
					RandomElement[rchild] = RandomElement[i];
					RandomElement[i] = mid;
					i = rchild;
				}
				else if (RandomElement[rchild] >= RandomElement[i] && RandomElement[lchild] == RandomElement[i])
				{
					ElemenType mid = RandomElement[rchild];
					RandomElement[rchild] = RandomElement[i];
					RandomElement[i] = mid;
					i = rchild;
				}
				else
					break;
			}
			else
			{
				if (RandomElement[lchild] > RandomElement[i])
				{
					ElemenType mid = RandomElement[lchild];
					RandomElement[lchild] = RandomElement[i];
					RandomElement[i] = mid;
					i = lchild;
				}
				else
					break;
			}
		}
	}
	if (maxormin == 2)
	{
		for (int i = root; i < RandomElement.size(); )
		{
			int lchild = i * 2 + 1;
			int rchild = lchild + 1;
			if (lchild >= RandomElement.size())
				break;
			if (rchild < RandomElement.size())
			{
				if (RandomElement[lchild] < RandomElement[i] && RandomElement[rchild] < RandomElement[i])
				{
					if (RandomElement[rchild] <= RandomElement[lchild])
					{
						ElemenType mid = RandomElement[rchild];
						RandomElement[rchild] = RandomElement[i];
						RandomElement[i] = mid;
						i = rchild;
					}
					else
					{
						ElemenType mid = RandomElement[lchild];
						RandomElement[lchild] = RandomElement[i];
						RandomElement[i] = mid;
						i = lchild;
					}
				}
				else if (RandomElement[lchild] <= RandomElement[i] && RandomElement[rchild] == RandomElement[i])
				{
					ElemenType mid = RandomElement[lchild];
					RandomElement[lchild] = RandomElement[i];
					RandomElement[i] = mid;
					i = lchild;
				}
				else if (RandomElement[lchild] <= RandomElement[i] && RandomElement[rchild] > RandomElement[i])
				{
					ElemenType mid = RandomElement[lchild];
					RandomElement[lchild] = RandomElement[i];
					RandomElement[i] = mid;
					i = lchild;
				}
				else if (RandomElement[rchild] <= RandomElement[i] && RandomElement[lchild] > RandomElement[i])
				{
					ElemenType mid = RandomElement[rchild];
					RandomElement[rchild] = RandomElement[i];
					RandomElement[i] = mid;
					i = rchild;
				}
				else if (RandomElement[rchild] <= RandomElement[i] && RandomElement[lchild] == RandomElement[i])
				{
					ElemenType mid = RandomElement[rchild];
					RandomElement[rchild] = RandomElement[i];
					RandomElement[i] = mid;
					i = rchild;
				}
				else
					break;
			}
			else
			{
				if (RandomElement[lchild] < RandomElement[i])
				{
					ElemenType mid = RandomElement[lchild];
					RandomElement[lchild] = RandomElement[i];
					RandomElement[i] = mid;
					i = lchild;
				}
				else
					break;
			}
		}
	}
	return;
}

ElemenType HeapOperate::DeleteHeapRoot(vector <ElemenType> & HeapData)
{
	if (HeapOperate::IsEmptyHeap(HeapData) == 1)
		return ElemenTypical;
	ElemenType returnele;
	returnele = *HeapData.begin();
	HeapData[0] = *(HeapData.end() - 1);
	HeapData.pop_back();

	Change2Heap(HeapData, 0, HeapOperate::MaxorMin);//�������һ�������ϵ���

	return returnele;
}

void HeapOperate::CreateHeap(vector <ElemenType> & RandomElement)
//����Ϊ�������У������������õ���Ӧ�Ķ����д浽HeapData��
//�����һ��һ�����룬��ô��nlogn���㷨��������n�������㷨
//�±������n�������㷨
{
	if (RandomElement.size() <= 1)
	{
		//Heap::HeapData = RandomElement;
		//return RandomElement;
		return;
	}

	for (int i = ceil(double((RandomElement.size() - 1) / 2.0)) - 1; i >= 0; i--)
	{
		Change2Heap(RandomElement, i, HeapOperate::MaxorMin);
	}
	//RandomElement = Heap::HeapData;
	//return RandomElement;
	return;

}
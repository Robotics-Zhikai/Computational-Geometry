#include "Heap.h"


void HeapOperate::SetMaxsizeHeap(int MaxSize)
{
	HeapOperate::MaxSize = MaxSize;
}

int HeapOperate::IsFullHeap(vector <ElemenType> HeapData)
{
	if (HeapData.size() > HeapOperate::MaxSize)
	{
		cout << "元素超过了最大值，这是不允许的！" << endl;
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
//以root为根节点，调整对应的子树为Heap,当然必须是在一定基础上调整
//复杂度为logn
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

	Change2Heap(HeapData, 0, HeapOperate::MaxorMin);//这就是在一定基础上调整

	return returnele;
}

void HeapOperate::CreateHeap(vector <ElemenType> & RandomElement)
//输入为任意序列，经过堆整理后得到对应的堆序列存到HeapData中
//如果是一个一个插入，那么是nlogn的算法，但是有n的线性算法
//下边这个是n的线性算法
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
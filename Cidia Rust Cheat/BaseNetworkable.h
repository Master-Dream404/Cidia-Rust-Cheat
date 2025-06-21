#pragma once
#include <string>
#include "Vectors.h"
class BaseNetworkable
{
	// So we use the static basegamemode__C in order to then access basenetworkable through the inheritance chain as basenetworkable itself is in a guarded region
/*
	{
	  "Name": "BaseNetworkable_TypeInfo",
	  "Signature": "BaseNetworkable_c*"
	},
*/
	uint64_t Class = 0x554F828;
	//Dump.cs / DummyDLL
	uint64_t StaticField = 0xB8;// Static Padding To Access Static Fields
	uint64_t ClientEntities = 0x0; // public static global::BaseNetworkable.EntityRealm clientEntities; 	public static %f4fcdf85d1b93204bf773ccba340d1274c47bdaf<BaseNetworkable.%ef51496c4fc233e37bc4cd0c7808ce6184edde1a> %0b3c7cdffd8074ec2e65a551b3832d944a0ced29;
	uint64_t EntityList = 0x10; // private ListDictionary<NetworkableId, global::BaseNetworkable> entityList; 		private %f4fcdf85d1b93204bf773ccba340d1274c47bdaf<ListDictionary<NetworkableId, BaseNetworkable>> %5a35885c0d901ae196b5647fdc219f3f8a3900f4;


	//These next two are a little tricky and you will require dump.cs
	//il2cpp dumper cant retrieve these offsets since they depend on what they are instantiated with
	//this explanation is for BufferList, which is in: public class ListDictionary<TKey, TVal>
	//the fields start at 0x10, this is because System.Object takes up 8 bytes and we need to allign to native word size
	//we are trying to calculate the offset of private BufferList<TVal> vals;
	//each var is a class reference, we can consider them 0x8 apart
	//so private BufferList<TVal> vals; is (0x10 + 0x8 + 0x8 + 0x8) with 0x10 being System.Object and three class refernces being added
	// this was to calculate BufferList, but the same Logic can be applied for the other, i have put the classes and their vars in comments

	uint64_t BufferList = 0x28; // public class ListDictionary<TKey, TVal> -> private BufferList<TVal> vals;
	uint64_t ObjectList = 0x18; // public class BufferList<T> -> private T[] buffer             (the int is a pointer, so 8 bytes rather than 4)
	uint32_t ObjectListSize = 0x10;

	/*

		// Token: 0x04002A5D RID: 10845
	[Token(Token = "0x4002A5D")]
	[FieldOffset(Offset = "0x48")]
	private string _prefabName;

	// Token: 0x04002A68 RID: 10856
	[Token(Token = "0x4002A68")]
	[FieldOffset(Offset = "0x48")]
	private string %c93df98286069c28f449cba54aec5638c6ccefa7;

	// Token: 0x04002A69 RID: 10857
	[Token(Token = "0x4002A69")]
	[FieldOffset(Offset = "0x50")]
	private string %0ba130f38297881da378aebfc6c225f965916a29;
	*/

public:
	BaseNetworkable();
	void ItterateEntities();
	unsigned int GetObjectSize();
	uintptr_t GetObjectList();
	uintptr_t GetElement(int index);
	std::string GetElementClassName(uintptr_t element);
	Vector3 GetObjectPosition(uintptr_t object);
	uintptr_t GetObjectComponent(uintptr_t object);
	std::string GetClassNameE(uintptr_t object);
};
#define unsafe_read(Addr, Type) (((((ULONG64)Addr) > 0x400000) && (((ULONG64)Addr + sizeof(Type)) < 0x00007FFFFFFF0000)) ? *(Type*)((ULONG64)Addr) : Type{})
#define safe_memcpy(Dst, Src, Size) safe_memcpy_wrapper(((ULONG64)Dst), ((ULONG64)Src), Size)
#define safe_write(Addr, Data, Type) if ((((ULONG64)Addr) > 0x400000) && (((ULONG64)Addr + sizeof(Type)) < 0x00007FFFFFFF0000)) { *(Type*)((ULONG64)Addr) = (Data); }

inline void safe_memcpy_wrapper(ULONG64 Dst, ULONG64 Src, ULONG Sz)
{
	if ((((ULONG64)Dst) > 0x400000) && (((ULONG64)Dst + Sz) < 0x00007FFFFFFF0000))
	{
		while (true)
		{
			//copy 8 byte
			if (Sz >= 8)
			{
				*(ULONG64*)Dst = *(ULONG64*)Src;
				Dst += 8; Src += 8; Sz -= 8;
			}

			//copy 4 byte
			else if (Sz >= 4)
			{
				*(ULONG*)Dst = *(ULONG*)Src;
				Dst += 4; Src += 4; Sz -= 4;
			}

			//copy 2 byte
			else if (Sz >= 2)
			{
				*(WORD*)Dst = *(WORD*)Src;
				Dst += 2; Src += 2; Sz -= 2;
			}

			//copy last byte
			else if (Sz)
			{
				*(BYTE*)Dst = *(BYTE*)Src;
				break;
			}

			//if(Sz == 0)
			else
				break;
		}
	}
}

template<typename t>
t readnew(uintptr_t addr) {
	if (addr < 0xffffff)
		return t();
	if (addr > 0x7fffffff0000)
		return t();

	return *reinterpret_cast<t*>(addr);
}

template<typename t>
bool writenew(uintptr_t addr, t buffer) {
	*reinterpret_cast<t*>(addr) = buffer;
	return true;
}

uintptr_t hook_virtual_function(const char* classname, const char* function_to_hook, void* target, const char* name_space);
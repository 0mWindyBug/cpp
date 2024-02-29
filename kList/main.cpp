#include <main.h>



void DriverUnload(
	_In_ PDRIVER_OBJECT DriverObject
)
{

	DbgPrint("[*] kList unloaded\n");
}


EXTERN_C NTSTATUS DriverEntry(
	_In_ PDRIVER_OBJECT DriverObject,
	_In_ PUNICODE_STRING RegistryPath
)
{
	UNREFERENCED_PARAMETER(RegistryPath);
	NTSTATUS status = STATUS_SUCCESS;

	kList<String> list;
	String str;
	String str2;
	UNICODE_STRING SomeValue = RTL_CONSTANT_STRING(L"hello");
	UNICODE_STRING SomeSecondValue = RTL_CONSTANT_STRING(L"hello2");
	str2.value = SomeSecondValue;
	str.value = SomeValue;
	list.insert(&str);
	list.insert(&str2);

	DbgPrint("[*] number of elements : %d\n", list.count_elements());



	String strs;
	String str2s;
	UNICODE_STRING SomeValues = RTL_CONSTANT_STRING(L"hello");
	UNICODE_STRING SomeSecondValues = RTL_CONSTANT_STRING(L"hello3");
	str2s.value = SomeSecondValues;
	strs.value = SomeValues;

	if (list.is_present(strs))
		DbgPrint("[*] present\n");
	if (list.is_present(str2s))
		DbgPrint("[*] present\n");


	list.destroy();

	DbgPrint("[*] number of elements : %d\n", list.count_elements());

	DriverObject->DriverUnload = DriverUnload;
	DbgPrint("[*] kList loaded!\n");

	return status;

}
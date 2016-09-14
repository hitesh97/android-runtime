#include "V8GlobalHelpers.h"
#include "ArgConverter.h"
#include "CallbackHandlers.h"
#include "include/v8.h"

using namespace v8;
using namespace std;

Local<String> tns::JsonStringifyObject(Isolate* isolate, Handle<v8::Value> value)
{
	if (value.IsEmpty()) {
		return String::Empty(isolate);
	}

	auto stringifyFunction = CallbackHandlers::isolateToJsonStringify.find(isolate)->second;
	auto func = Local<Function>::New(isolate, *stringifyFunction);
	Local<Value> args[] = { value };

	auto result = func->Call(Undefined(isolate), 1, args);

	return result->ToString(isolate);
}

Local<Value> tns::V8GetHiddenValue(const Local<Object>& obj, const string& propName)
{
	// TODO: Pete: Temporary - this function is changed in the new v8 api refactoring branch
	auto isolate = Isolate::GetCurrent();
	auto s = ArgConverter::ConvertToV8String(isolate, propName);
	return obj->GetHiddenValue(s);
}

bool tns::V8SetHiddenValue(const Local<Object>& obj, const string& propName, const Local<Value>& value)
{
// TODO: Pete: Temporary - this function is changed in the new v8 api refactoring branch
	auto isolate = Isolate::GetCurrent();
	auto s = ArgConverter::ConvertToV8String(isolate, propName);
	return obj->SetHiddenValue(s, value);
}

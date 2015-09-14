#include <node.h>
extern "C" {
#include <mkdio.h>
}

namespace discount {

using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::HandleScope;
using v8::Isolate;
using v8::Context;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Exception;

/**
 * parse(strMarkdown, opts)
 *
 */
void Markup (const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    Local<Context> ctx = isolate->GetCurrentContext();

    int argc = args.Length();
    if (argc == 0 || argc > 2) {
        isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "Incorrect number of arguments")));
        return;
    }
    if ((!args[0]->IsString() && !args[0]->IsStringObject())
            || (argc == 2 && !args[1]->IsObject())) {
        isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "Incorrect argument type")));
        return;
    }

    String::Utf8Value arg0(args[0]->ToString());
    char *strMarkdown = *arg0;
    Local<Object> opts;
    int flags = 0;
    Local<Value>
        keyNoLinks          = String::NewFromUtf8(isolate, "noLinks"),
        keyNoImage          = String::NewFromUtf8(isolate, "noImage"),
        keyNoPants          = String::NewFromUtf8(isolate, "noPants"),
        keyNoHTML           = String::NewFromUtf8(isolate, "noHTML"),
        keyStrict           = String::NewFromUtf8(isolate, "strict"),
        keyTagText          = String::NewFromUtf8(isolate, "tagText"),
        keyNoExt            = String::NewFromUtf8(isolate, "noExt"),
        keyCdata            = String::NewFromUtf8(isolate, "cdata"),
        keyNoSuperscript    = String::NewFromUtf8(isolate, "noSuperscript"),
        keyNoRelaxed        = String::NewFromUtf8(isolate, "noRelaxed"),
        keyNoTables         = String::NewFromUtf8(isolate, "noTables"),
        keyNoStrikethrough  = String::NewFromUtf8(isolate, "noStrikethrough"),
        keyToc              = String::NewFromUtf8(isolate, "toc"),
        keyMd1Compat        = String::NewFromUtf8(isolate, "md1Compat"),
        keyAutolink         = String::NewFromUtf8(isolate, "autolink"),
        keySafelink         = String::NewFromUtf8(isolate, "safelink"),
        keyNoHeader         = String::NewFromUtf8(isolate, "noHeader"),
        keyTabStop          = String::NewFromUtf8(isolate, "tabStop"),
        keyNoDivQuote       = String::NewFromUtf8(isolate, "noDivQuote"),
        keyNoAlphaList      = String::NewFromUtf8(isolate, "noAlphaList"),
        keyNoDList          = String::NewFromUtf8(isolate, "noDList"),
        keyExtraFootnote    = String::NewFromUtf8(isolate, "extraFootnote");

    if (argc == 2) {
      opts = args[1]->ToObject();
    } else {
      flags = 0;
    }

    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world"));
}

void init (Local<Object> exports) {
    NODE_SET_METHOD(exports, "markup", Markup);
}

NODE_MODULE(discount, init)

}

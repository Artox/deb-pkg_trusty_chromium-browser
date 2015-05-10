// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef Response_h
#define Response_h

#include "bindings/core/v8/Dictionary.h"
#include "bindings/core/v8/ScriptWrappable.h"
#include "bindings/modules/v8/UnionTypesModules.h"
#include "modules/fetch/Body.h"
#include "modules/fetch/FetchResponseData.h"
#include "modules/fetch/Headers.h"
#include "platform/blob/BlobData.h"
#include "platform/heap/Handle.h"

namespace blink {

class Blob;
class BodyStreamBuffer;
class DOMArrayBuffer;
class ExceptionState;
class ResponseInit;
class WebServiceWorkerResponse;

typedef BlobOrArrayBufferOrArrayBufferViewOrUSVString BodyInit;

class Response final : public Body {
    DEFINE_WRAPPERTYPEINFO();
public:
    ~Response() override { }

    // From Response.idl:
    static Response* create(ExecutionContext*, ExceptionState&);
    static Response* create(ExecutionContext*, const BodyInit&, const Dictionary&, ExceptionState&);

    static Response* create(ExecutionContext*, Blob*, const ResponseInit&, ExceptionState&);
    static Response* create(ExecutionContext*, FetchResponseData*);
    static Response* create(ExecutionContext*, const WebServiceWorkerResponse&);

    static Response* createClone(const Response&);

    const FetchResponseData* response() const { return m_response; }

    // From Response.idl:
    String type() const;
    String url() const;
    unsigned short status() const;
    String statusText() const;
    Headers* headers() const;

    // From Response.idl:
    Response* clone(ExceptionState&) const;

    void populateWebServiceWorkerResponse(WebServiceWorkerResponse&);

    bool hasBody() const;

    PassRefPtr<BlobDataHandle> blobDataHandle() const override;
    BodyStreamBuffer* buffer() const override;
    String contentTypeForBuffer() const override;

    PassRefPtr<BlobDataHandle> internalBlobDataHandle() const;
    BodyStreamBuffer* internalBuffer() const;
    String internalContentTypeForBuffer() const;

    void trace(Visitor*) override;

private:
    explicit Response(const Response&);
    explicit Response(ExecutionContext*);
    Response(ExecutionContext*, FetchResponseData*);

    const Member<FetchResponseData> m_response;
    const Member<Headers> m_headers;
};

} // namespace blink

#endif // Response_h
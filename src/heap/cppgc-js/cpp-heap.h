// Copyright 2020 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8_HEAP_CPPGC_JS_CPP_HEAP_H_
#define V8_HEAP_CPPGC_JS_CPP_HEAP_H_

#include "include/v8.h"
#include "src/base/macros.h"
#include "src/heap/cppgc/heap-base.h"

namespace v8 {

class Isolate;

namespace internal {

// A C++ heap implementation used with V8 to implement unified heap.
class V8_EXPORT_PRIVATE CppHeap final : public cppgc::internal::HeapBase,
                                        public v8::EmbedderHeapTracer {
 public:
  CppHeap(v8::Isolate* isolate, size_t custom_spaces);

  HeapBase& AsBase() { return *this; }
  const HeapBase& AsBase() const { return *this; }

  void RegisterV8References(
      const std::vector<std::pair<void*, void*> >& embedder_fields) final;
  void TracePrologue(TraceFlags flags) final;
  bool AdvanceTracing(double deadline_in_ms) final;
  bool IsTracingDone() final;
  void TraceEpilogue(TraceSummary* trace_summary) final;
  void EnterFinalPause(EmbedderStackState stack_state) final;

 private:
  Isolate& isolate_;
  bool marking_done_ = false;
};

}  // namespace internal
}  // namespace v8

#endif  // V8_HEAP_CPPGC_JS_CPP_HEAP_H_

// Copyright 2020 Tencent
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once
#include <memory>

#include "easy_transformers/core/tensor.h"

namespace easy_transformers {
namespace layers {

class BertAttention {
 public:
  BertAttention(core::Tensor qkv_weight, core::Tensor qkv_bias,
                core::Tensor dense_weight, core::Tensor dense_bias,
                core::Tensor layer_norm_weight, core::Tensor layer_norm_bias,
                int64_t num_attention_heads)
      : qkv_weight_(std::move(qkv_weight)),  //(768, 768)
        qkv_bias_(std::move(qkv_bias)),
        dense_weight_(std::move(dense_weight)),
        dense_bias_(std::move(dense_bias)),
        layer_norm_weight_(std::move(layer_norm_weight)),  //(768)
        layer_norm_bias_(std::move(layer_norm_bias)),
        num_attention_heads_(num_attention_heads) {
    EnforceShapeAndType();
  }
  void EnforceShapeAndType() const;

  void operator()(const core::Tensor &input_tensor,
                  const core::Tensor &attention_mask,
                  core::Tensor *output) const;

 private:
  core::Tensor qkv_weight_;
  core::Tensor qkv_bias_;
  core::Tensor dense_weight_;
  core::Tensor dense_bias_;
  core::Tensor layer_norm_weight_;
  core::Tensor layer_norm_bias_;
  int64_t num_attention_heads_;
};

}  // namespace layers
}  // namespace easy_transformers
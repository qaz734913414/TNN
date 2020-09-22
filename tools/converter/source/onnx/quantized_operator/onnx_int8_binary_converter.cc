// Tencent is pleased to support the open source community by making TNN available.
//
// Copyright (C) 2020 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// https://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#include "tools/converter/source/onnx/onnx_base_converter.h"

namespace TNN_CONVERTER {
DECLARE_OP_CONVERTER(Int8Binary);

std::string OnnxInt8BinaryConverter::TNNOpType(const onnx::NodeProto &node, bool quantized_model) {
    if (node.op_type() == "Int8Add") {
        return "QuantizedAdd";
    }
    return "";
}

TNN_NS::ActivationType OnnxInt8BinaryConverter::ActivationType(const onnx::NodeProto &node) {
    return TNN_NS::ActivationType_None;
}

TNN_NS::Status OnnxInt8BinaryConverter::exec(tnn::NetStructure &net_structure, tnn::NetResource &net_resource,
                                             const onnx::NodeProto &node,
                                             std::map<std::string, const onnx::TensorProto *> proxy_initializers_map,
                                             std::map<std::string, std::shared_ptr<OnnxProxyNode>> proxy_nodes,
                                             bool &quantized_model) {
    auto param       = new TNN_NS::MultidirBroadcastLayerParam;
    auto cur_layer   = net_structure.layers.back();
    cur_layer->param = std::shared_ptr<TNN_NS::LayerParam>(param);
    param->type      = cur_layer->type_str;
    param->name      = cur_layer->name;
    param->quantized = true;
    param->weight_input_index = -1;
    return TNN_NS::TNN_CONVERT_OK;
}

REGISTER_CONVERTER(Int8Binary, Int8Binary);
}  // namespace TNN_CONVERTER
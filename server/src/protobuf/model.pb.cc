// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: model.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "model.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace model {

namespace {

const ::google::protobuf::Descriptor* Entity_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Entity_reflection_ = NULL;
const ::google::protobuf::Descriptor* Relation_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Relation_reflection_ = NULL;
const ::google::protobuf::Descriptor* Index_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Index_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* DataType_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_model_2eproto() {
  protobuf_AddDesc_model_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "model.proto");
  GOOGLE_CHECK(file != NULL);
  Entity_descriptor_ = file->message_type(0);
  static const int Entity_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Entity, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Entity, type_),
  };
  Entity_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Entity_descriptor_,
      Entity::default_instance_,
      Entity_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Entity, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Entity, _unknown_fields_),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Entity, _extensions_),
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Entity));
  Relation_descriptor_ = file->message_type(1);
  static const int Relation_offsets_[1] = {
  };
  Relation_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Relation_descriptor_,
      Relation::default_instance_,
      Relation_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Relation, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Relation, _unknown_fields_),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Relation, _extensions_),
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Relation));
  Index_descriptor_ = file->message_type(2);
  static const int Index_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Index, type_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Index, key_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Index, entity_),
  };
  Index_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Index_descriptor_,
      Index::default_instance_,
      Index_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Index, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Index, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Index));
  DataType_descriptor_ = file->enum_type(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_model_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Entity_descriptor_, &Entity::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Relation_descriptor_, &Relation::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Index_descriptor_, &Index::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_model_2eproto() {
  delete Entity::default_instance_;
  delete Entity_reflection_;
  delete Relation::default_instance_;
  delete Relation_reflection_;
  delete Index::default_instance_;
  delete Index_reflection_;
}

void protobuf_AddDesc_model_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\013model.proto\022\005model\",\n\006Entity\022\n\n\002id\030\001 \002"
    "(\014\022\014\n\004type\030\002 \002(\r*\010\010\003\020\200\200\200\200\002\"\024\n\010Relation*\010"
    "\010\001\020\200\200\200\200\002\"2\n\005Index\022\014\n\004type\030\001 \002(\r\022\013\n\003key\030\002"
    " \002(\014\022\016\n\006entity\030\003 \002(\014*i\n\010DataType\022\010\n\004META"
    "\020\000\022\n\n\006ENTITY\020\001\022\014\n\010RELATION\020\002\022\t\n\005EVENT\020\003\022"
    "\014\n\010ACTIVITY\020\004\022\t\n\005INDEX\020\005\022\013\n\007ARCHIVE\020\006\022\010\n"
    "\004LAST\020d", 247);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "model.proto", &protobuf_RegisterTypes);
  Entity::default_instance_ = new Entity();
  Relation::default_instance_ = new Relation();
  Index::default_instance_ = new Index();
  Entity::default_instance_->InitAsDefaultInstance();
  Relation::default_instance_->InitAsDefaultInstance();
  Index::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_model_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_model_2eproto {
  StaticDescriptorInitializer_model_2eproto() {
    protobuf_AddDesc_model_2eproto();
  }
} static_descriptor_initializer_model_2eproto_;
const ::google::protobuf::EnumDescriptor* DataType_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return DataType_descriptor_;
}
bool DataType_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 100:
      return true;
    default:
      return false;
  }
}


// ===================================================================

#ifndef _MSC_VER
const int Entity::kIdFieldNumber;
const int Entity::kTypeFieldNumber;
#endif  // !_MSC_VER

Entity::Entity()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Entity::InitAsDefaultInstance() {
}

Entity::Entity(const Entity& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Entity::SharedCtor() {
  _cached_size_ = 0;
  id_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  type_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Entity::~Entity() {
  SharedDtor();
}

void Entity::SharedDtor() {
  if (id_ != &::google::protobuf::internal::kEmptyString) {
    delete id_;
  }
  if (this != default_instance_) {
  }
}

void Entity::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Entity::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Entity_descriptor_;
}

const Entity& Entity::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_model_2eproto();
  return *default_instance_;
}

Entity* Entity::default_instance_ = NULL;

Entity* Entity::New() const {
  return new Entity;
}

void Entity::Clear() {
  _extensions_.Clear();
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_id()) {
      if (id_ != &::google::protobuf::internal::kEmptyString) {
        id_->clear();
      }
    }
    type_ = 0u;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Entity::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required bytes id = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_id()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_type;
        break;
      }

      // required uint32 type = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_type:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &type_)));
          set_has_type();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        if ((24u <= tag)) {
          DO_(_extensions_.ParseField(tag, input, default_instance_,
                                      mutable_unknown_fields()));
          continue;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void Entity::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required bytes id = 1;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteBytes(
      1, this->id(), output);
  }

  // required uint32 type = 2;
  if (has_type()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->type(), output);
  }

  // Extension range [3, 536870912)
  _extensions_.SerializeWithCachedSizes(
      3, 536870912, output);

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Entity::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required bytes id = 1;
  if (has_id()) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        1, this->id(), target);
  }

  // required uint32 type = 2;
  if (has_type()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->type(), target);
  }

  // Extension range [3, 536870912)
  target = _extensions_.SerializeWithCachedSizesToArray(
      3, 536870912, target);

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Entity::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required bytes id = 1;
    if (has_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::BytesSize(
          this->id());
    }

    // required uint32 type = 2;
    if (has_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->type());
    }

  }
  total_size += _extensions_.ByteSize();

  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Entity::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Entity* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Entity*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Entity::MergeFrom(const Entity& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_id()) {
      set_id(from.id());
    }
    if (from.has_type()) {
      set_type(from.type());
    }
  }
  _extensions_.MergeFrom(from._extensions_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Entity::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Entity::CopyFrom(const Entity& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Entity::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;


  if (!_extensions_.IsInitialized()) return false;  return true;
}

void Entity::Swap(Entity* other) {
  if (other != this) {
    std::swap(id_, other->id_);
    std::swap(type_, other->type_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
    _extensions_.Swap(&other->_extensions_);
  }
}

::google::protobuf::Metadata Entity::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Entity_descriptor_;
  metadata.reflection = Entity_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
#endif  // !_MSC_VER

Relation::Relation()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Relation::InitAsDefaultInstance() {
}

Relation::Relation(const Relation& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Relation::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Relation::~Relation() {
  SharedDtor();
}

void Relation::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Relation::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Relation::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Relation_descriptor_;
}

const Relation& Relation::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_model_2eproto();
  return *default_instance_;
}

Relation* Relation::default_instance_ = NULL;

Relation* Relation::New() const {
  return new Relation;
}

void Relation::Clear() {
  _extensions_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Relation::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
        ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
      return true;
    }
    if ((8u <= tag)) {
      DO_(_extensions_.ParseField(tag, input, default_instance_,
                                  mutable_unknown_fields()));
      continue;
    }
    DO_(::google::protobuf::internal::WireFormat::SkipField(
          input, tag, mutable_unknown_fields()));
  }
  return true;
#undef DO_
}

void Relation::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // Extension range [1, 536870912)
  _extensions_.SerializeWithCachedSizes(
      1, 536870912, output);

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Relation::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // Extension range [1, 536870912)
  target = _extensions_.SerializeWithCachedSizesToArray(
      1, 536870912, target);

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Relation::ByteSize() const {
  int total_size = 0;

  total_size += _extensions_.ByteSize();

  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Relation::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Relation* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Relation*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Relation::MergeFrom(const Relation& from) {
  GOOGLE_CHECK_NE(&from, this);
  _extensions_.MergeFrom(from._extensions_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Relation::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Relation::CopyFrom(const Relation& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Relation::IsInitialized() const {


  if (!_extensions_.IsInitialized()) return false;  return true;
}

void Relation::Swap(Relation* other) {
  if (other != this) {
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
    _extensions_.Swap(&other->_extensions_);
  }
}

::google::protobuf::Metadata Relation::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Relation_descriptor_;
  metadata.reflection = Relation_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int Index::kTypeFieldNumber;
const int Index::kKeyFieldNumber;
const int Index::kEntityFieldNumber;
#endif  // !_MSC_VER

Index::Index()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Index::InitAsDefaultInstance() {
}

Index::Index(const Index& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Index::SharedCtor() {
  _cached_size_ = 0;
  type_ = 0u;
  key_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  entity_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Index::~Index() {
  SharedDtor();
}

void Index::SharedDtor() {
  if (key_ != &::google::protobuf::internal::kEmptyString) {
    delete key_;
  }
  if (entity_ != &::google::protobuf::internal::kEmptyString) {
    delete entity_;
  }
  if (this != default_instance_) {
  }
}

void Index::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Index::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Index_descriptor_;
}

const Index& Index::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_model_2eproto();
  return *default_instance_;
}

Index* Index::default_instance_ = NULL;

Index* Index::New() const {
  return new Index;
}

void Index::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    type_ = 0u;
    if (has_key()) {
      if (key_ != &::google::protobuf::internal::kEmptyString) {
        key_->clear();
      }
    }
    if (has_entity()) {
      if (entity_ != &::google::protobuf::internal::kEmptyString) {
        entity_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Index::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 type = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &type_)));
          set_has_type();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_key;
        break;
      }

      // required bytes key = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_key:
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_key()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_entity;
        break;
      }

      // required bytes entity = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_entity:
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_entity()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void Index::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required uint32 type = 1;
  if (has_type()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->type(), output);
  }

  // required bytes key = 2;
  if (has_key()) {
    ::google::protobuf::internal::WireFormatLite::WriteBytes(
      2, this->key(), output);
  }

  // required bytes entity = 3;
  if (has_entity()) {
    ::google::protobuf::internal::WireFormatLite::WriteBytes(
      3, this->entity(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Index::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required uint32 type = 1;
  if (has_type()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->type(), target);
  }

  // required bytes key = 2;
  if (has_key()) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        2, this->key(), target);
  }

  // required bytes entity = 3;
  if (has_entity()) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        3, this->entity(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Index::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 type = 1;
    if (has_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->type());
    }

    // required bytes key = 2;
    if (has_key()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::BytesSize(
          this->key());
    }

    // required bytes entity = 3;
    if (has_entity()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::BytesSize(
          this->entity());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Index::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Index* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Index*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Index::MergeFrom(const Index& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_type()) {
      set_type(from.type());
    }
    if (from.has_key()) {
      set_key(from.key());
    }
    if (from.has_entity()) {
      set_entity(from.entity());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Index::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Index::CopyFrom(const Index& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Index::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;

  return true;
}

void Index::Swap(Index* other) {
  if (other != this) {
    std::swap(type_, other->type_);
    std::swap(key_, other->key_);
    std::swap(entity_, other->entity_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Index::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Index_descriptor_;
  metadata.reflection = Index_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace model

// @@protoc_insertion_point(global_scope)

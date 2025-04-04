#include "CondCore/CondDB/interface/Binary.h"
#include "CondCore/CondDB/interface/Exception.h"
//
#include "CoralBase/Blob.h"
//
#include <cstring>

#include <cstring>
#include <memory>
#include <openssl/sha.h>

cond::Binary::Binary() : m_data(new coral::Blob(0)) {}

cond::Binary::Binary(const void* data, size_t size) : m_data(new coral::Blob(size)) {
  ::memcpy(m_data->startingAddress(), data, size);
}

cond::Binary::Binary(const coral::Blob& data) : m_data(new coral::Blob(data.size())) {
  ::memcpy(m_data->startingAddress(), data.startingAddress(), data.size());
}

cond::Binary::Binary(const Binary& rhs) : m_data(rhs.m_data) {}

cond::Binary& cond::Binary::operator=(const Binary& rhs) {
  if (this != &rhs) {
    m_data = rhs.m_data;
  }
  return *this;
}

const coral::Blob& cond::Binary::get() const { return *m_data; }

void cond::Binary::copy(const std::string& source) {
  m_data = std::make_shared<coral::Blob>(source.size());
  ::memcpy(m_data->startingAddress(), source.c_str(), source.size());
}

const void* cond::Binary::data() const {
  if (!m_data.get())
    throwException("Binary data can't be accessed.", "Binary::data");
  return m_data->startingAddress();
}
void* cond::Binary::data() {
  if (!m_data.get())
    throwException("Binary data can't be accessed.", "Binary::data");
  return m_data->startingAddress();
}

size_t cond::Binary::size() const {
  if (!m_data.get())
    throwException("Binary data can't be accessed.", "Binary::size");
  return m_data->size();
}

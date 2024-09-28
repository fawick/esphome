#pragma once

#include <cstddef>
#include <cstdint>

namespace esphome {
namespace ota {

enum OTAResponseTypes {
  OTA_RESPONSE_OK = 0x00,
  OTA_RESPONSE_REQUEST_AUTH = 0x01,
  OTA_RESPONSE_REQUEST_MD5 = 0x02,

  OTA_RESPONSE_HEADER_OK = 0x40,
  OTA_RESPONSE_AUTH_OK = 0x41,
  OTA_RESPONSE_UPDATE_PREPARE_OK = 0x42,
  OTA_RESPONSE_BIN_MD5_OK = 0x43,
  OTA_RESPONSE_RECEIVE_OK = 0x44,
  OTA_RESPONSE_UPDATE_END_OK = 0x45,
  OTA_RESPONSE_SUPPORTS_COMPRESSION = 0x46,
  OTA_RESPONSE_CHUNK_OK = 0x47,
  OTA_RESPONSE_SUPPORTS_EXTENDED = 0x48,
  OTA_RESPONSE_READ_PREPARE_OK = 0x49,
  OTA_RESPONSE_READ_END_OK = 0x4A,

  OTA_RESPONSE_ERROR_MAGIC = 0x80,
  OTA_RESPONSE_ERROR_UPDATE_PREPARE = 0x81,
  OTA_RESPONSE_ERROR_AUTH_INVALID = 0x82,
  OTA_RESPONSE_ERROR_WRITING_FLASH = 0x83,
  OTA_RESPONSE_ERROR_UPDATE_END = 0x84,
  OTA_RESPONSE_ERROR_INVALID_BOOTSTRAPPING = 0x85,
  OTA_RESPONSE_ERROR_WRONG_CURRENT_FLASH_CONFIG = 0x86,
  OTA_RESPONSE_ERROR_WRONG_NEW_FLASH_CONFIG = 0x87,
  OTA_RESPONSE_ERROR_ESP8266_NOT_ENOUGH_SPACE = 0x88,
  OTA_RESPONSE_ERROR_ESP32_NOT_ENOUGH_SPACE = 0x89,
  OTA_RESPONSE_ERROR_NO_UPDATE_PARTITION = 0x8A,
  OTA_RESPONSE_ERROR_MD5_MISMATCH = 0x8B,
  OTA_RESPONSE_ERROR_RP2040_NOT_ENOUGH_SPACE = 0x8C,
  OTA_RESPONSE_ERROR_UNKNOWN_PARTITION_INFO_VERSION = 0x8D,
  OTA_RESPONSE_ERROR_BIN_TYPE_NOT_SUPPORTED = 0x8E,
  OTA_RESPONSE_ERROR_ESP32_REGISTERING_PARTITION = 0x8F,
  OTA_RESPONSE_ERROR_PARTITION_NOT_FOUND = 0x90,
  OTA_RESPONSE_ERROR_UNKNOWN_COMMAND = 0x91,
  OTA_RESPONSE_ERROR_ABORT_OVERRIDE = 0x92,
  OTA_RESPONSE_ERROR_SOCKET_READ = 0x93,
  OTA_RESPONSE_ERROR_READ_NOT_SUPPORTED = 0x94,
  OTA_RESPONSE_ERROR_READING_FLASH = 0x95,
  OTA_RESPONSE_ERROR_UNKNOWN = 0xFF,
};

enum OTABinType {
  OTA_BIN_APP = 1,
  OTA_BIN_BOOTLOADER = 2,
  OTA_BIN_PARTITION_TABLE = 3,
  OTA_BIN_PARTITION = 4,
};

struct OTAPartitionType {
  OTABinType type;
  uint8_t part_type;
  uint8_t part_subtype;
  uint8_t part_index;
  char part_label[16];
};

class OTABackend {
 public:
  virtual ~OTABackend() = default;
  virtual OTAResponseTypes begin(OTAPartitionType bin_type, size_t &image_size) = 0;
  virtual void set_update_md5(const char *md5) = 0;
  virtual OTAResponseTypes write(uint8_t *data, size_t len) = 0;
  virtual OTAResponseTypes read(uint8_t *data, size_t len) { return OTA_RESPONSE_ERROR_READ_NOT_SUPPORTED; }
  virtual OTAResponseTypes end() = 0;
  virtual void abort() = 0;
  virtual bool supports_compression() = 0;
  virtual bool supports_writing_bootloader() { return false; }
  virtual bool supports_writing_partition_table() { return false; }
  virtual bool supports_writing_partitions() { return false; }
  virtual bool supports_reading() { return false; }
};

}  // namespace ota
}  // namespace esphome

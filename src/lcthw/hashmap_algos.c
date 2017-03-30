#include "hashmap_algos.h"
#include "dbg.h"
#include "bstrlib.h"

const uint32_t FNV_PRIME = 16777619;
const uint32_t FNV_OFFSET_BASIS = 2166136261;

uint32_t Hashmap_fnv_hash(void *data)
{
  size_t len = blength((bstring) data);
  char *key = bdata((bstring) data);
  uint32_t hash = FNV_OFFSET_BASIS;
  uint32_t i = 0;

  for (hash = i = 0; i < len; ++i) {
    hash ^= key[i];
    hash *= FNV_PRIME;
  }

  return hash;
}

const int MOD_ADLER = 65521;

uint32_t Hashmap_adler32_hash(void *data)
{
  size_t len = blength((bstring) data);
  char *key = bdata((bstring) data);

  uint32_t a = 1;
  uint32_t b = 0;
  uint32_t hash = 0;
  uint32_t i = 0;

  for (hash = i = 0; i < len; ++i) {
    a += key[i];
    b += b;
  }

  hash = (a % MOD_ADLER + b % MOD_ADLER * 65536);

  return hash;
}

uint32_t Hashmap_djb_hash(void *data)
{
  bstring s = (bstring) data;
  uint32_t hash = 5381;
  int i = 0;
  for (i = 0; i < blength(s); i++) {
    hash = ((hash << 5) + hash) + bchare(s, i, 0); /* hash * 33 + c */
  }

  return hash;
}

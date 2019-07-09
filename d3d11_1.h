#pragma once

#define __d3d11_h__

#define __cdecl
#define WINAPI
#define STDMETHODCALLTYPE
#define STDMETHOD(method) virtual HRESULT STDMETHODCALLTYPE method
#define STDMETHODIMP HRESULT STDMETHODCALLTYPE
#define PURE = 0
#define UNREFERENCED_PARAMETER(P) (P)

#include <cstdint>
#include <cstdio>
#include <cstdarg>
#include <cmath>
#include <cstring>
#include <chrono>
#include <string>
#include "dxgiformat.h"

typedef void* PVOID;
typedef PVOID HANDLE;
typedef uint32_t DWORD;
typedef int BOOL;
typedef char CHAR;
typedef int INT;
typedef unsigned int UINT;
typedef const char* LPCSTR;
typedef unsigned short WORD;
typedef wchar_t WCHAR;
typedef unsigned long UINT64;
typedef unsigned long ULONGLONG;
typedef unsigned long DWORD64;
typedef WCHAR *PWSTR;

#define INVALID_HANDLE_VALUE nullptr
#define _MAX_FNAME 260
#define MAX_PATH 260
#define _MAX_PATH 260
#define _MAX_EXT 260
#define _MAX_DRIVE 260
#define _MAX_DIR 260

#define D3D11_IA_VERTEX_INPUT_STRUCTURE_ELEMENT_COUNT 32
#define D3D11_16BIT_INDEX_STRIP_CUT_VALUE uint16_t(-1)
#define D3D11_32BIT_INDEX_STRIP_CUT_VALUE uint32_t(-1)
#define D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT 32
#define D3D11_REQ_MULTI_ELEMENT_STRUCTURE_SIZE_IN_BYTES 2048
#define D3D11_APPEND_ALIGNED_ELEMENT 0

typedef enum D3D11_INPUT_CLASSIFICATION {
  D3D11_INPUT_PER_VERTEX_DATA = 0,
  D3D11_INPUT_PER_INSTANCE_DATA = 1
} D3D11_INPUT_CLASSIFICATION;

typedef struct D3D11_INPUT_ELEMENT_DESC {
  LPCSTR                     SemanticName;
  UINT                       SemanticIndex;
  DXGI_FORMAT                Format;
  UINT                       InputSlot;
  UINT                       AlignedByteOffset;
  D3D11_INPUT_CLASSIFICATION InputSlotClass;
  UINT                       InstanceDataStepRate;
} D3D11_INPUT_ELEMENT_DESC;

typedef struct _FILETIME {
  DWORD dwLowDateTime;
  DWORD dwHighDateTime;
} FILETIME, *PFILETIME, *LPFILETIME;

typedef struct _WIN32_FIND_DATAA {
  DWORD    dwFileAttributes;
  FILETIME ftCreationTime;
  FILETIME ftLastAccessTime;
  FILETIME ftLastWriteTime;
  DWORD    nFileSizeHigh;
  DWORD    nFileSizeLow;
  DWORD    dwReserved0;
  DWORD    dwReserved1;
  CHAR     cFileName[MAX_PATH];
  CHAR     cAlternateFileName[14];
  DWORD    dwFileType;
  DWORD    dwCreatorType;
  WORD     wFinderFlags;
} WIN32_FIND_DATAA, *PWIN32_FIND_DATAA, *LPWIN32_FIND_DATAA;

typedef struct _WIN32_FIND_DATAW {
  DWORD    dwFileAttributes;
  FILETIME ftCreationTime;
  FILETIME ftLastAccessTime;
  FILETIME ftLastWriteTime;
  DWORD    nFileSizeHigh;
  DWORD    nFileSizeLow;
  DWORD    dwReserved0;
  DWORD    dwReserved1;
  WCHAR    cFileName[MAX_PATH];
  WCHAR    cAlternateFileName[14];
  DWORD    dwFileType;
  DWORD    dwCreatorType;
  WORD     wFinderFlags;
} WIN32_FIND_DATAW, *PWIN32_FIND_DATAW, *LPWIN32_FIND_DATAW;

inline int _finite(double x) {
  return std::isfinite(x) ? 1 : 0;
}

template<typename T, size_t N>
constexpr size_t _countof(T const (&)[N]) noexcept {
  return N;
}

template<typename T>
inline T __min(T x, T y) {
  return std::min(x, y);
}

inline void* _aligned_malloc(std::size_t size, std::size_t alignment) {
  return std::aligned_alloc(alignment, size);
}

inline void _aligned_free(void *ptr) {
  std::free(ptr);
}

template <size_t size>
inline int swprintf_s(wchar_t (&buffer)[size], const wchar_t *format, ...) {
  int ret;
  va_list args;
  va_start(args, format);
  ret = wprintf(buffer, size, format, args);
  va_end(args);
  return ret;
}

inline int _stricmp(const char *string1, const char *string2) {
  return strcasecmp(string1, string2);
}

template <size_t size>  
inline void wcscpy_s(wchar_t (&strDestination)[size], const wchar_t *strSource) {
  wcscpy(strDestination, strSource);
}

inline void _splitpath_s(
  const char * path,
  char * drive,
  size_t driveNumberOfElements,
  char * dir,
  size_t dirNumberOfElements,
  char * fname,
  size_t nameNumberOfElements,
  char * ex,
  size_t extNumberOfElements)
{
  const std::string path_(path);

  auto dot_pos = path_.rfind('.');
  auto slash_pos = path_.rfind('/');
  if (slash_pos != std::string::npos && dot_pos < slash_pos) {
    dot_pos = std::string::npos;
  }

  if (dot_pos == std::string::npos) {
    dot_pos = path_.length();
  } else if (ex) {
    strcpy(ex, path_.substr(dot_pos).c_str());
  }

  if (slash_pos == std::string::npos) {
    if (fname) {
      strcpy(fname, path_.substr(0, dot_pos).c_str());
    }
    if (dir) {
      strcpy(dir, "");
    }
  } else {
    if (fname) {
      strcpy(fname, path_.substr(slash_pos + 1, dot_pos - slash_pos - 1).c_str());
    }
    if (dir) {
      strcpy(dir, path_.substr(0, slash_pos).c_str());
    }
  }

  if (drive) {
    strcpy(drive, "");
  }
}

inline void _wsplitpath_s(
  const wchar_t * path,
  wchar_t * drive,
  size_t driveNumberOfElements,
  wchar_t * dir,
  size_t dirNumberOfElements,
  wchar_t * fname,
  size_t nameNumberOfElements,
  wchar_t * ex,
  size_t extNumberOfElements)
{
  const std::wstring path_(path);

  auto dot_pos = path_.rfind('.');
  auto slash_pos = path_.rfind('/');
  if (slash_pos != std::wstring::npos && dot_pos < slash_pos) {
    dot_pos = std::wstring::npos;
  }

  if (dot_pos == std::wstring::npos) {
    dot_pos = path_.length();
  } else if (ex) {
    wcscpy(ex, path_.substr(dot_pos).c_str());
  }

  if (slash_pos == std::wstring::npos) {
    if (fname) {
      wcscpy(fname, path_.substr(0, dot_pos).c_str());
    }
    if (dir) {
      wcscpy(dir, L"");
    }
  } else {
    if (fname) {
      wcscpy(fname, path_.substr(slash_pos + 1, dot_pos - slash_pos - 1).c_str());
    }
    if (dir) {
      wcscpy(dir, path_.substr(0, slash_pos).c_str());
    }
  }

  if (drive) {
    wcscpy(drive, L"");
  }
}

inline void _wmakepath_s(
  wchar_t *path,
  size_t sizeInWords,
  const wchar_t *drive,
  const wchar_t *dir,
  const wchar_t *fname,
  const wchar_t *ext
)
{
  if (dir == nullptr) {
    wcscpy(path, fname);
    wcscat(path, ext);
  } else if (ext == nullptr) {
    wcscpy(path, dir);
    wcscat(path, L"/");
    wcscat(path, fname);
  } else {
    wcscpy(path, dir);
    wcscat(path, L"/");
    wcscat(path, fname);
    wcscat(path, ext);
  }
}

template <size_t size>  
inline void _wmakepath_s(  
  wchar_t (&path)[size],
  const wchar_t *drive,
  const wchar_t *dir,
  const wchar_t *fname,
  const wchar_t *ext
) {
  _wmakepath_s(path, size, drive, dir, fname, ext);
}

inline void _makepath_s(
  char *path,
  size_t sizeInWords,
  const char *drive,
  const char *dir,
  const char *fname,
  const char *ext
)
{
  if (dir == nullptr) {
    strcpy(path, fname);
    strcat(path, ext);
  } else if (ext == nullptr) {
    strcpy(path, dir);
    strcat(path, "/");
    strcat(path, fname);
  } else {
    strcpy(path, dir);
    strcat(path, "/");
    strcat(path, fname);
    strcat(path, ext);
  }
}

template <size_t size>  
inline void _makepath_s(  
  char (&path)[size],
  const char *drive,
  const char *dir,
  const char *fname,
  const char *ext
) {
  _makepath_s(path, size, drive, dir, fname, ext);
}

inline ULONGLONG GetTickCount64() {
  auto now = std::chrono::high_resolution_clock::now();
  return now.time_since_epoch().count();
}

enum HRESULT {
  S_OK = 0,
  S_FALSE = 1,
  E_FAIL = 2,
  E_INVALIDARG = 3,
  E_UNEXPECTED = 4,
  E_OUTOFMEMORY = 5,
  ERROR_ARITHMETIC_OVERFLOW = 6,
  ERROR_NOT_SUPPORTED = 7,
  ERROR_INVALID_NAME = 8,
  E_BOUNDS = 9,
  E_POINTER = 10,
  ERROR_INVALID_DATA = 11,
  E_ABORT = 12,
  ERROR_FILE_NOT_FOUND = 13,
  E_NOTIMPL = 14
};

#define SUCCEEDED(h) ((h) == S_OK)
#define FAILED(x) ((x) != S_OK)
#define GetLastError() S_OK
#define HRESULT_FROM_WIN32(x) (x)

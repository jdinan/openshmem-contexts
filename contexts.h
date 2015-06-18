#ifndef CONTEXT_H_INCL
#define CONTEXT_H_INCL

#include <stddef.h>

#define SHMEM_CTX_DEFAULT 0
#define SHMEM_DOMAIN_DEFAULT 0

typedef int shmem_ctx_t;
typedef int shmem_domain_t;

void shmem_domain_create(int thread_level, int num_domains, shmem_domain_t domains[]);

void shmem_domain_destroy(int num_domains, shmem_domain_t domains[]);
int shmem_ctx_create(shmem_domain_t domain, shmem_ctx_t *ctx);
void shmem_ctx_destroy(shmem_ctx_t ctx);
void shmem_ctx_fence(shmem_ctx_t ctx);
void shmem_ctx_quiet(shmem_ctx_t ctx);

void shmem_sync(int PE_start, int logPE_stride, int PE_size, long *pSync);
void shmem_sync_all(void); 

#define SHMEM_PUTGET_ALIGN_OPS_DECLARE(STYPE) \
    void shmem_ctx_put##STYPE(void *dest, const void *source, size_t nelems, int pe, shmem_ctx_t ctx);                                      \
    void shmem_ctx_iput##STYPE(void *dest, const void *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems, int pe, shmem_ctx_t ctx);       \
    void shmem_ctx_get##STYPE(void *dest, const void *source, size_t nelems, int pe, shmem_ctx_t ctx);                                      \
    void shmem_ctx_iget##STYPE(void *dest, const void *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems, int pe, shmem_ctx_t ctx);       \
    void shmem_ctx_iget##STYPE(void *dest, const void *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems, int pe, shmem_ctx_t ctx);       \
    void shmem_ctx_put##STYPE##_nb(void *dest, const void *source, size_t nelems, int pe, shmem_ctx_t ctx);                                 \
    void shmem_ctx_iput##STYPE##_nb(void *dest, const void *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems, int pe, shmem_ctx_t ctx);  \
    void shmem_ctx_get##STYPE##_nb(void *dest, const void *source, size_t nelems, int pe, shmem_ctx_t ctx);                                 \
    void shmem_ctx_iget##STYPE##_nb(void *dest, const void *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems, int pe, shmem_ctx_t ctx);  \
    void shmem_ctx_iget##STYPE##_nb(void *dest, const void *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems, int pe, shmem_ctx_t ctx);

#define SHMEM_PG_OPS_DECLARE(STYPE, CTYPE) \
    void shmem_ctx_##STYPE##_p(CTYPE *addr, CTYPE value, int pe, shmem_ctx_t ctx);                                                          \
    CTYPE shmem_ctx_##STYPE##_g(CTYPE *addr, int pe, shmem_ctx_t ctx);

#define SHMEM_PUTGET_OPS_DECLARE(STYPE, CTYPE) \
    void shmem_ctx_##STYPE##_put(CTYPE *dest, const CTYPE *source, size_t nelems, int pe, shmem_ctx_t ctx);                                 \
    void shmem_ctx_##STYPE##_iput(CTYPE *dest, const CTYPE *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems, int pe, shmem_ctx_t ctx);  \
    void shmem_ctx_##STYPE##_put_nb(CTYPE *dest, const CTYPE *source, size_t nelems, int pe, shmem_ctx_t ctx);                              \
    void shmem_ctx_##STYPE##_iput_nb(CTYPE *dest, const CTYPE *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems, int pe, shmem_ctx_t ctx); \
                                                                                                                                            \
    void shmem_ctx_##STYPE##_get(CTYPE *dest, const CTYPE *source, size_t nelems, int pe, shmem_ctx_t ctx);                                 \
    void shmem_ctx_##STYPE##_iget(CTYPE *dest, const CTYPE *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems, int pe, shmem_ctx_t ctx);  \
    void shmem_ctx_##STYPE##_get_nb(CTYPE *dest, const CTYPE *source, size_t nelems, int pe, shmem_ctx_t ctx);                              \
    void shmem_ctx_##STYPE##_iget_nb(CTYPE *dest, const CTYPE *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems, int pe, shmem_ctx_t ctx);

#define SHMEM_ATOMIC_OPS_DECLARE(STYPE, CTYPE) \
    void shmem_##STYPE##_add(CTYPE *dest, CTYPE value, int pe, shmem_ctx_t ctx);                                                            \
    CTYPE shmem_##STYPE##_cswap(CTYPE *dest, CTYPE cond, CTYPE value, int pe, shmem_ctx_t ctx);                                             \
    CTYPE shmem_##STYPE##_finc(CTYPE *dest, int pe, shmem_ctx_t ctx);                                                                       \
    void shmem_##STYPE##_inc(CTYPE *dest, int pe, shmem_ctx_t ctx);                                                                         \
    CTYPE shmem_##STYPE##_fadd(CTYPE *dest, CTYPE value, int pe, shmem_ctx_t ctx);                                                          \

#define SHMEM_SWAP_OP_DECLARE(STYPE, CTYPE) \
    CTYPE shmem_##STYPE##_swap(CTYPE *dest, CTYPE value, int pe, shmem_ctx_t ctx);

SHMEM_PUTGET_ALIGN_OPS_DECLARE(32)
SHMEM_PUTGET_ALIGN_OPS_DECLARE(64)
SHMEM_PUTGET_ALIGN_OPS_DECLARE(128)
SHMEM_PUTGET_ALIGN_OPS_DECLARE(mem)

SHMEM_PG_OPS_DECLARE(char, char)
SHMEM_PG_OPS_DECLARE(short, short)
SHMEM_PG_OPS_DECLARE(int, int)
SHMEM_PG_OPS_DECLARE(long, long)
SHMEM_PG_OPS_DECLARE(longlong, long long)
SHMEM_PG_OPS_DECLARE(float, float)
SHMEM_PG_OPS_DECLARE(double, double)
SHMEM_PG_OPS_DECLARE(longdouble, long double)

SHMEM_PUTGET_OPS_DECLARE(short, short)
SHMEM_PUTGET_OPS_DECLARE(int, int)
SHMEM_PUTGET_OPS_DECLARE(long, long)
SHMEM_PUTGET_OPS_DECLARE(longlong, long long)
SHMEM_PUTGET_OPS_DECLARE(float, float)
SHMEM_PUTGET_OPS_DECLARE(double, double)
SHMEM_PUTGET_OPS_DECLARE(longdouble, long double)

SHMEM_ATOMIC_OPS_DECLARE(int, int)
SHMEM_ATOMIC_OPS_DECLARE(long, long)
SHMEM_ATOMIC_OPS_DECLARE(longlong, long long)

SHMEM_SWAP_OP_DECLARE(int, int)
SHMEM_SWAP_OP_DECLARE(long, long)
SHMEM_SWAP_OP_DECLARE(longlong, long long)
SHMEM_SWAP_OP_DECLARE(float, float)
SHMEM_SWAP_OP_DECLARE(double, double)

long shmem_ctx_swap(long *dest, long value, int pe, shmem_ctx_t ctx);

#endif /* CONTEXT_H_INCL */

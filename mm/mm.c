#include <mm.h>

static char heap_buff[MM_SIZE_HEAP];

static struct mm_heap_s g_kmmheap;
static FAR void* heap_start = NULL;
static size_t heap_size = 0;

#ifndef MM_REGION_CNT
#define MM_REGION_CNT (1)
#endif

void mm_init(void)
{
	heap_start = heap_buff;
	heap_size = MM_SIZE_HEAP;
	kmm_initialize(heap_start, heap_size);
}

void kmm_initialize(FAR void* heap_start, size_t heap_size)
{
	mm_initialize(&g_kmmheap, heap_start, heap_size);
#if defined(MM_REGION2)
	mm_addregion(&g_kmmheap, (FAR void*)MM_REGION2_ADDR, MM_REGION2_SIZE);
#endif
}

FAR void* malloc(size_t size)
{
	return mm_malloc(&g_kmmheap, size);
}

FAR void* realloc(FAR void* oldmem, size_t newsize)
{
	return mm_realloc(&g_kmmheap, oldmem, newsize);
}

void free(FAR void* mem)
{
	mm_free(&g_kmmheap, mem);
}

int mallinfo(FAR struct mallinfo* info)
{
	return mm_mallinfo(&g_kmmheap, info);
}

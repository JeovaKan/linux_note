/*
 * 物理内存用到的一些数据结构
 */

 	/* 内存节点信息 */
 	typedef struct pglist_data {
		zone_t node_zones[MAX_NR_ZONES];
		zonelist_t node_zonelists[NR_GFPINDEX];
		struct page *node_mem_map;
		unsigned long *valid_addr_bitmap;
		struct bootmem_data *bdata;
		unsigned long node_start_paddr;
		unsigned long node_start_mapnr;
		unsigned long node_size;
		int node_id;
		struct pglist_data *node_next;
	} pg_data_t;
	
 	typedef struct zonelist_struct {
		zone_t * zones [MAX_NR_ZONES+1]; // NULL delimited
		int gfp_mask;
	} zonelist_t;

	typedef struct zone_struct {
		/*
		 * Commonly accessed fields:
		 */
		spinlock_t		lock;
		unsigned long		offset;
		unsigned long		free_pages;
		unsigned long		inactive_clean_pages;
		unsigned long		inactive_dirty_pages;
		unsigned long		pages_min, pages_low, pages_high;

		/*
		 * free areas of different sizes
		 */
		struct list_head	inactive_clean_list;
		free_area_t		free_area[MAX_ORDER];

		/*
		 * rarely used fields:
		 */
		char			*name;
		unsigned long		size;
		/*
		 * Discontig memory support fields.
		 */
		struct pglist_data	*zone_pgdat;
		unsigned long		zone_start_paddr;
		unsigned long		zone_start_mapnr;
		struct page		*zone_mem_map;
	} zone_t;

	typedef struct free_area_struct {
		struct list_head	free_list;
		unsigned int		*map;
	} free_area_t;

	typedef struct page {
		struct list_head list;
		struct address_space *mapping;
		unsigned long index;
		struct page *next_hash;
		atomic_t count;
		unsigned long flags;	/* atomic flags, some possibly updated asynchronously */
		struct list_head lru;
		unsigned long age;
		wait_queue_head_t wait;
		struct page **pprev_hash;
		struct buffer_head * buffers;
		void *virtual; /* non-NULL if kmapped */
		struct zone_struct *zone;
	} mem_map_t;
/************************************************************************************************************/

	struct mm_struct {
		struct vm_area_struct * mmap;		/* list of VMAs */
		struct vm_area_struct * mmap_avl;	/* tree of VMAs */
		struct vm_area_struct * mmap_cache;	/* last find_vma result */
		pgd_t * pgd;
		atomic_t mm_users;			/* How many users with user space? */
		atomic_t mm_count;			/* How many references to "struct mm_struct" (users count as 1) */
		int map_count;				/* number of VMAs */
		struct semaphore mmap_sem;
		spinlock_t page_table_lock;

		struct list_head mmlist;		/* List of all active mm's */

		unsigned long start_code, end_code, start_data, end_data;
		unsigned long start_brk, brk, start_stack;
		unsigned long arg_start, arg_end, env_start, env_end;
		unsigned long rss, total_vm, locked_vm;
		unsigned long def_flags;
		unsigned long cpu_vm_mask;
		unsigned long swap_cnt;	/* number of pages to swap on next pass */
		unsigned long swap_address;	

		/* Architecture-specific MM context */
		mm_context_t context;
	};

	
	struct vm_area_struct {
		struct mm_struct * vm_mm;	/* VM area parameters */
		unsigned long vm_start;
		unsigned long vm_end;

		/* linked list of VM areas per task, sorted by address */
		struct vm_area_struct *vm_next;

		pgprot_t vm_page_prot;
		unsigned long vm_flags;

		/* AVL tree of VM areas per task, sorted by address */
		short vm_avl_height;
		struct vm_area_struct * vm_avl_left;
		struct vm_area_struct * vm_avl_right;

		/* For areas with an address space and backing store,
		 * one of the address_space->i_mmap{,shared} lists,
		 * for shm areas, the list of attaches, otherwise unused.
		 */
		struct vm_area_struct *vm_next_share;
		struct vm_area_struct **vm_pprev_share;

		struct vm_operations_struct * vm_ops;
		unsigned long vm_pgoff;		/* offset in PAGE_SIZE units, *not* PAGE_CACHE_SIZE */
		struct file * vm_file;
		unsigned long vm_raend;
		void * vm_private_data;		/* was vm_pte (shared mem) */
	};


































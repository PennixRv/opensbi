/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2021 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#ifndef __TIMER_ACLINT_MTIMER_H__
#define __TIMER_ACLINT_MTIMER_H__

#include <sbi/sbi_types.h>

#define ACLINT_MTIMER_ALIGN		0x8
#define ACLINT_MTIMER_MAX_HARTS		4095

#define ACLINT_DEFAULT_MTIME_OFFSET	0x7ff8
#define ACLINT_DEFAULT_MTIME_SIZE	0x8
#define ACLINT_DEFAULT_MTIMECMP_OFFSET	0x0000
#define ACLINT_DEFAULT_MTIMECMP_SIZE	0x7ff8

#define CLINT_MTIMER_OFFSET		0x4000

struct aclint_mtimer_data {
	/* Public details */
	unsigned long mtime_addr;
	unsigned long mtime_size;
	unsigned long mtimecmp_addr;
	unsigned long mtimecmp_size;
	u32 first_hartid;
	u32 hart_count;
	bool has_64bit_mmio;
	/* Private details (initialized and used by ACLINT MTIMER library) */
	struct aclint_mtimer_data *time_delta_reference;
	unsigned long time_delta_computed;
	u64 time_delta;
	u64 (*time_rd)(volatile u64 *addr);
	void (*time_wr)(bool timecmp, u64 value, volatile u64 *addr);
};

int aclint_mtimer_warm_init(void);

int aclint_mtimer_cold_init(struct aclint_mtimer_data *mt,
			    struct aclint_mtimer_data *reference);

#endif

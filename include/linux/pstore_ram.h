<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2010 Marco Stornelli <marco.stornelli@gmail.com>
 * Copyright (C) 2011 Kees Cook <keescook@chromium.org>
 * Copyright (C) 2011 Google, Inc.
 */

#अगर_अघोषित __LINUX_PSTORE_RAM_H__
#घोषणा __LINUX_PSTORE_RAM_H__

#समावेश <linux/compiler.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/pstore.h>
#समावेश <linux/types.h>

/*
 * Choose whether access to the RAM zone requires locking or not.  If a zone
 * can be written to from dअगरferent CPUs like with ftrace क्रम example, then
 * PRZ_FLAG_NO_LOCK is used. For all other हालs, locking is required.
 */
#घोषणा PRZ_FLAG_NO_LOCK	BIT(0)
/*
 * If a PRZ should only have a single-boot lअगरeसमय, this marks it as
 * getting wiped after its contents get copied out after boot.
 */
#घोषणा PRZ_FLAG_ZAP_OLD	BIT(1)

काष्ठा persistent_ram_buffer;
काष्ठा rs_control;

काष्ठा persistent_ram_ecc_info अणु
	पूर्णांक block_size;
	पूर्णांक ecc_size;
	पूर्णांक symsize;
	पूर्णांक poly;
	uपूर्णांक16_t *par;
पूर्ण;

/**
 * काष्ठा persistent_ram_zone - Details of a persistent RAM zone (PRZ)
 *                              used as a pstore backend
 *
 * @paddr:	physical address of the mapped RAM area
 * @size:	size of mapping
 * @label:	unique name of this PRZ
 * @type:	frontend type क्रम this PRZ
 * @flags:	holds PRZ_FLAGS_* bits
 *
 * @buffer_lock:
 *	locks access to @buffer "size" bytes and "start" offset
 * @buffer:
 *	poपूर्णांकer to actual RAM area managed by this PRZ
 * @buffer_size:
 *	bytes in @buffer->data (not including any trailing ECC bytes)
 *
 * @par_buffer:
 *	poपूर्णांकer पूर्णांकo @buffer->data containing ECC bytes क्रम @buffer->data
 * @par_header:
 *	poपूर्णांकer पूर्णांकo @buffer->data containing ECC bytes क्रम @buffer header
 *	(i.e. all fields up to @data)
 * @rs_decoder:
 *	RSLIB instance क्रम करोing ECC calculations
 * @corrected_bytes:
 *	ECC corrected bytes accounting since boot
 * @bad_blocks:
 *	ECC uncorrectable bytes accounting since boot
 * @ecc_info:
 *	ECC configuration details
 *
 * @old_log:
 *	saved copy of @buffer->data prior to most recent wipe
 * @old_log_size:
 *	bytes contained in @old_log
 *
 */
काष्ठा persistent_ram_zone अणु
	phys_addr_t paddr;
	माप_प्रकार size;
	व्योम *vaddr;
	अक्षर *label;
	क्रमागत pstore_type_id type;
	u32 flags;

	raw_spinlock_t buffer_lock;
	काष्ठा persistent_ram_buffer *buffer;
	माप_प्रकार buffer_size;

	अक्षर *par_buffer;
	अक्षर *par_header;
	काष्ठा rs_control *rs_decoder;
	पूर्णांक corrected_bytes;
	पूर्णांक bad_blocks;
	काष्ठा persistent_ram_ecc_info ecc_info;

	अक्षर *old_log;
	माप_प्रकार old_log_size;
पूर्ण;

काष्ठा persistent_ram_zone *persistent_ram_new(phys_addr_t start, माप_प्रकार size,
			u32 sig, काष्ठा persistent_ram_ecc_info *ecc_info,
			अचिन्हित पूर्णांक memtype, u32 flags, अक्षर *label);
व्योम persistent_ram_मुक्त(काष्ठा persistent_ram_zone *prz);
व्योम persistent_ram_zap(काष्ठा persistent_ram_zone *prz);

पूर्णांक persistent_ram_ग_लिखो(काष्ठा persistent_ram_zone *prz, स्थिर व्योम *s,
			 अचिन्हित पूर्णांक count);
पूर्णांक persistent_ram_ग_लिखो_user(काष्ठा persistent_ram_zone *prz,
			      स्थिर व्योम __user *s, अचिन्हित पूर्णांक count);

व्योम persistent_ram_save_old(काष्ठा persistent_ram_zone *prz);
माप_प्रकार persistent_ram_old_size(काष्ठा persistent_ram_zone *prz);
व्योम *persistent_ram_old(काष्ठा persistent_ram_zone *prz);
व्योम persistent_ram_मुक्त_old(काष्ठा persistent_ram_zone *prz);
sमाप_प्रकार persistent_ram_ecc_string(काष्ठा persistent_ram_zone *prz,
	अक्षर *str, माप_प्रकार len);

/*
 * Ramoops platक्रमm data
 * @mem_size	memory size क्रम ramoops
 * @mem_address	physical memory address to contain ramoops
 */

#घोषणा RAMOOPS_FLAG_FTRACE_PER_CPU	BIT(0)

काष्ठा ramoops_platक्रमm_data अणु
	अचिन्हित दीर्घ	mem_size;
	phys_addr_t	mem_address;
	अचिन्हित पूर्णांक	mem_type;
	अचिन्हित दीर्घ	record_size;
	अचिन्हित दीर्घ	console_size;
	अचिन्हित दीर्घ	ftrace_size;
	अचिन्हित दीर्घ	pmsg_size;
	पूर्णांक		max_reason;
	u32		flags;
	काष्ठा persistent_ram_ecc_info ecc_info;
पूर्ण;

#पूर्ण_अगर

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * APEI Error Record Serialization Table support
 *
 * ERST is a way provided by APEI to save and retrieve hardware error
 * inक्रमmation to and from a persistent store.
 *
 * For more inक्रमmation about ERST, please refer to ACPI Specअगरication
 * version 4.0, section 17.4.
 *
 * Copyright 2010 Intel Corp.
 *   Author: Huang Ying <ying.huang@पूर्णांकel.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/acpi.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/cper.h>
#समावेश <linux/nmi.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/pstore.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mm.h> /* kvमुक्त() */
#समावेश <acpi/apei.h>

#समावेश "apei-internal.h"

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) "ERST: " fmt

/* ERST command status */
#घोषणा ERST_STATUS_SUCCESS			0x0
#घोषणा ERST_STATUS_NOT_ENOUGH_SPACE		0x1
#घोषणा ERST_STATUS_HARDWARE_NOT_AVAILABLE	0x2
#घोषणा ERST_STATUS_FAILED			0x3
#घोषणा ERST_STATUS_RECORD_STORE_EMPTY		0x4
#घोषणा ERST_STATUS_RECORD_NOT_FOUND		0x5

#घोषणा ERST_TAB_ENTRY(tab)						\
	((काष्ठा acpi_whea_header *)((अक्षर *)(tab) +			\
				     माप(काष्ठा acpi_table_erst)))

#घोषणा SPIN_UNIT		100			/* 100ns */
/* Firmware should respond within 1 milliseconds */
#घोषणा FIRMWARE_TIMEOUT	(1 * NSEC_PER_MSEC)
#घोषणा FIRMWARE_MAX_STALL	50			/* 50us */

पूर्णांक erst_disable;
EXPORT_SYMBOL_GPL(erst_disable);

अटल काष्ठा acpi_table_erst *erst_tab;

/* ERST Error Log Address Range attributes */
#घोषणा ERST_RANGE_RESERVED	0x0001
#घोषणा ERST_RANGE_NVRAM	0x0002
#घोषणा ERST_RANGE_SLOW		0x0004

/*
 * ERST Error Log Address Range, used as buffer क्रम पढ़ोing/writing
 * error records.
 */
अटल काष्ठा erst_erange अणु
	u64 base;
	u64 size;
	व्योम __iomem *vaddr;
	u32 attr;
पूर्ण erst_erange;

/*
 * Prevent ERST पूर्णांकerpreter to run simultaneously, because the
 * corresponding firmware implementation may not work properly when
 * invoked simultaneously.
 *
 * It is used to provide exclusive accessing क्रम ERST Error Log
 * Address Range too.
 */
अटल DEFINE_RAW_SPINLOCK(erst_lock);

अटल अंतरभूत पूर्णांक erst_त्रुटि_सं(पूर्णांक command_status)
अणु
	चयन (command_status) अणु
	हाल ERST_STATUS_SUCCESS:
		वापस 0;
	हाल ERST_STATUS_HARDWARE_NOT_AVAILABLE:
		वापस -ENODEV;
	हाल ERST_STATUS_NOT_ENOUGH_SPACE:
		वापस -ENOSPC;
	हाल ERST_STATUS_RECORD_STORE_EMPTY:
	हाल ERST_STATUS_RECORD_NOT_FOUND:
		वापस -ENOENT;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक erst_समयकरोut(u64 *t, u64 spin_unit)
अणु
	अगर ((s64)*t < spin_unit) अणु
		pr_warn(FW_WARN "Firmware does not respond in time.\n");
		वापस 1;
	पूर्ण
	*t -= spin_unit;
	ndelay(spin_unit);
	touch_nmi_watchकरोg();
	वापस 0;
पूर्ण

अटल पूर्णांक erst_exec_load_var1(काष्ठा apei_exec_context *ctx,
			       काष्ठा acpi_whea_header *entry)
अणु
	वापस __apei_exec_पढ़ो_रेजिस्टर(entry, &ctx->var1);
पूर्ण

अटल पूर्णांक erst_exec_load_var2(काष्ठा apei_exec_context *ctx,
			       काष्ठा acpi_whea_header *entry)
अणु
	वापस __apei_exec_पढ़ो_रेजिस्टर(entry, &ctx->var2);
पूर्ण

अटल पूर्णांक erst_exec_store_var1(काष्ठा apei_exec_context *ctx,
				काष्ठा acpi_whea_header *entry)
अणु
	वापस __apei_exec_ग_लिखो_रेजिस्टर(entry, ctx->var1);
पूर्ण

अटल पूर्णांक erst_exec_add(काष्ठा apei_exec_context *ctx,
			 काष्ठा acpi_whea_header *entry)
अणु
	ctx->var1 += ctx->var2;
	वापस 0;
पूर्ण

अटल पूर्णांक erst_exec_subtract(काष्ठा apei_exec_context *ctx,
			      काष्ठा acpi_whea_header *entry)
अणु
	ctx->var1 -= ctx->var2;
	वापस 0;
पूर्ण

अटल पूर्णांक erst_exec_add_value(काष्ठा apei_exec_context *ctx,
			       काष्ठा acpi_whea_header *entry)
अणु
	पूर्णांक rc;
	u64 val;

	rc = __apei_exec_पढ़ो_रेजिस्टर(entry, &val);
	अगर (rc)
		वापस rc;
	val += ctx->value;
	rc = __apei_exec_ग_लिखो_रेजिस्टर(entry, val);
	वापस rc;
पूर्ण

अटल पूर्णांक erst_exec_subtract_value(काष्ठा apei_exec_context *ctx,
				    काष्ठा acpi_whea_header *entry)
अणु
	पूर्णांक rc;
	u64 val;

	rc = __apei_exec_पढ़ो_रेजिस्टर(entry, &val);
	अगर (rc)
		वापस rc;
	val -= ctx->value;
	rc = __apei_exec_ग_लिखो_रेजिस्टर(entry, val);
	वापस rc;
पूर्ण

अटल पूर्णांक erst_exec_stall(काष्ठा apei_exec_context *ctx,
			   काष्ठा acpi_whea_header *entry)
अणु
	u64 stall_समय;

	अगर (ctx->value > FIRMWARE_MAX_STALL) अणु
		अगर (!in_nmi())
			pr_warn(FW_WARN
			"Too long stall time for stall instruction: 0x%llx.\n",
				   ctx->value);
		stall_समय = FIRMWARE_MAX_STALL;
	पूर्ण अन्यथा
		stall_समय = ctx->value;
	udelay(stall_समय);
	वापस 0;
पूर्ण

अटल पूर्णांक erst_exec_stall_जबतक_true(काष्ठा apei_exec_context *ctx,
				      काष्ठा acpi_whea_header *entry)
अणु
	पूर्णांक rc;
	u64 val;
	u64 समयout = FIRMWARE_TIMEOUT;
	u64 stall_समय;

	अगर (ctx->var1 > FIRMWARE_MAX_STALL) अणु
		अगर (!in_nmi())
			pr_warn(FW_WARN
		"Too long stall time for stall while true instruction: 0x%llx.\n",
				   ctx->var1);
		stall_समय = FIRMWARE_MAX_STALL;
	पूर्ण अन्यथा
		stall_समय = ctx->var1;

	क्रम (;;) अणु
		rc = __apei_exec_पढ़ो_रेजिस्टर(entry, &val);
		अगर (rc)
			वापस rc;
		अगर (val != ctx->value)
			अवरोध;
		अगर (erst_समयकरोut(&समयout, stall_समय * NSEC_PER_USEC))
			वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक erst_exec_skip_next_inकाष्ठाion_अगर_true(
	काष्ठा apei_exec_context *ctx,
	काष्ठा acpi_whea_header *entry)
अणु
	पूर्णांक rc;
	u64 val;

	rc = __apei_exec_पढ़ो_रेजिस्टर(entry, &val);
	अगर (rc)
		वापस rc;
	अगर (val == ctx->value) अणु
		ctx->ip += 2;
		वापस APEI_EXEC_SET_IP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक erst_exec_जाओ(काष्ठा apei_exec_context *ctx,
			  काष्ठा acpi_whea_header *entry)
अणु
	ctx->ip = ctx->value;
	वापस APEI_EXEC_SET_IP;
पूर्ण

अटल पूर्णांक erst_exec_set_src_address_base(काष्ठा apei_exec_context *ctx,
					  काष्ठा acpi_whea_header *entry)
अणु
	वापस __apei_exec_पढ़ो_रेजिस्टर(entry, &ctx->src_base);
पूर्ण

अटल पूर्णांक erst_exec_set_dst_address_base(काष्ठा apei_exec_context *ctx,
					  काष्ठा acpi_whea_header *entry)
अणु
	वापस __apei_exec_पढ़ो_रेजिस्टर(entry, &ctx->dst_base);
पूर्ण

अटल पूर्णांक erst_exec_move_data(काष्ठा apei_exec_context *ctx,
			       काष्ठा acpi_whea_header *entry)
अणु
	पूर्णांक rc;
	u64 offset;
	व्योम *src, *dst;

	/* ioremap करोes not work in पूर्णांकerrupt context */
	अगर (in_पूर्णांकerrupt()) अणु
		pr_warn("MOVE_DATA can not be used in interrupt context.\n");
		वापस -EBUSY;
	पूर्ण

	rc = __apei_exec_पढ़ो_रेजिस्टर(entry, &offset);
	अगर (rc)
		वापस rc;

	src = ioremap(ctx->src_base + offset, ctx->var2);
	अगर (!src)
		वापस -ENOMEM;
	dst = ioremap(ctx->dst_base + offset, ctx->var2);
	अगर (!dst) अणु
		iounmap(src);
		वापस -ENOMEM;
	पूर्ण

	स_हटाओ(dst, src, ctx->var2);

	iounmap(src);
	iounmap(dst);

	वापस 0;
पूर्ण

अटल काष्ठा apei_exec_ins_type erst_ins_type[] = अणु
	[ACPI_ERST_READ_REGISTER] = अणु
		.flags = APEI_EXEC_INS_ACCESS_REGISTER,
		.run = apei_exec_पढ़ो_रेजिस्टर,
	पूर्ण,
	[ACPI_ERST_READ_REGISTER_VALUE] = अणु
		.flags = APEI_EXEC_INS_ACCESS_REGISTER,
		.run = apei_exec_पढ़ो_रेजिस्टर_value,
	पूर्ण,
	[ACPI_ERST_WRITE_REGISTER] = अणु
		.flags = APEI_EXEC_INS_ACCESS_REGISTER,
		.run = apei_exec_ग_लिखो_रेजिस्टर,
	पूर्ण,
	[ACPI_ERST_WRITE_REGISTER_VALUE] = अणु
		.flags = APEI_EXEC_INS_ACCESS_REGISTER,
		.run = apei_exec_ग_लिखो_रेजिस्टर_value,
	पूर्ण,
	[ACPI_ERST_NOOP] = अणु
		.flags = 0,
		.run = apei_exec_noop,
	पूर्ण,
	[ACPI_ERST_LOAD_VAR1] = अणु
		.flags = APEI_EXEC_INS_ACCESS_REGISTER,
		.run = erst_exec_load_var1,
	पूर्ण,
	[ACPI_ERST_LOAD_VAR2] = अणु
		.flags = APEI_EXEC_INS_ACCESS_REGISTER,
		.run = erst_exec_load_var2,
	पूर्ण,
	[ACPI_ERST_STORE_VAR1] = अणु
		.flags = APEI_EXEC_INS_ACCESS_REGISTER,
		.run = erst_exec_store_var1,
	पूर्ण,
	[ACPI_ERST_ADD] = अणु
		.flags = 0,
		.run = erst_exec_add,
	पूर्ण,
	[ACPI_ERST_SUBTRACT] = अणु
		.flags = 0,
		.run = erst_exec_subtract,
	पूर्ण,
	[ACPI_ERST_ADD_VALUE] = अणु
		.flags = APEI_EXEC_INS_ACCESS_REGISTER,
		.run = erst_exec_add_value,
	पूर्ण,
	[ACPI_ERST_SUBTRACT_VALUE] = अणु
		.flags = APEI_EXEC_INS_ACCESS_REGISTER,
		.run = erst_exec_subtract_value,
	पूर्ण,
	[ACPI_ERST_STALL] = अणु
		.flags = 0,
		.run = erst_exec_stall,
	पूर्ण,
	[ACPI_ERST_STALL_WHILE_TRUE] = अणु
		.flags = APEI_EXEC_INS_ACCESS_REGISTER,
		.run = erst_exec_stall_जबतक_true,
	पूर्ण,
	[ACPI_ERST_SKIP_NEXT_IF_TRUE] = अणु
		.flags = APEI_EXEC_INS_ACCESS_REGISTER,
		.run = erst_exec_skip_next_inकाष्ठाion_अगर_true,
	पूर्ण,
	[ACPI_ERST_GOTO] = अणु
		.flags = 0,
		.run = erst_exec_जाओ,
	पूर्ण,
	[ACPI_ERST_SET_SRC_ADDRESS_BASE] = अणु
		.flags = APEI_EXEC_INS_ACCESS_REGISTER,
		.run = erst_exec_set_src_address_base,
	पूर्ण,
	[ACPI_ERST_SET_DST_ADDRESS_BASE] = अणु
		.flags = APEI_EXEC_INS_ACCESS_REGISTER,
		.run = erst_exec_set_dst_address_base,
	पूर्ण,
	[ACPI_ERST_MOVE_DATA] = अणु
		.flags = APEI_EXEC_INS_ACCESS_REGISTER,
		.run = erst_exec_move_data,
	पूर्ण,
पूर्ण;

अटल अंतरभूत व्योम erst_exec_ctx_init(काष्ठा apei_exec_context *ctx)
अणु
	apei_exec_ctx_init(ctx, erst_ins_type, ARRAY_SIZE(erst_ins_type),
			   ERST_TAB_ENTRY(erst_tab), erst_tab->entries);
पूर्ण

अटल पूर्णांक erst_get_erange(काष्ठा erst_erange *range)
अणु
	काष्ठा apei_exec_context ctx;
	पूर्णांक rc;

	erst_exec_ctx_init(&ctx);
	rc = apei_exec_run(&ctx, ACPI_ERST_GET_ERROR_RANGE);
	अगर (rc)
		वापस rc;
	range->base = apei_exec_ctx_get_output(&ctx);
	rc = apei_exec_run(&ctx, ACPI_ERST_GET_ERROR_LENGTH);
	अगर (rc)
		वापस rc;
	range->size = apei_exec_ctx_get_output(&ctx);
	rc = apei_exec_run(&ctx, ACPI_ERST_GET_ERROR_ATTRIBUTES);
	अगर (rc)
		वापस rc;
	range->attr = apei_exec_ctx_get_output(&ctx);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार __erst_get_record_count(व्योम)
अणु
	काष्ठा apei_exec_context ctx;
	पूर्णांक rc;

	erst_exec_ctx_init(&ctx);
	rc = apei_exec_run(&ctx, ACPI_ERST_GET_RECORD_COUNT);
	अगर (rc)
		वापस rc;
	वापस apei_exec_ctx_get_output(&ctx);
पूर्ण

sमाप_प्रकार erst_get_record_count(व्योम)
अणु
	sमाप_प्रकार count;
	अचिन्हित दीर्घ flags;

	अगर (erst_disable)
		वापस -ENODEV;

	raw_spin_lock_irqsave(&erst_lock, flags);
	count = __erst_get_record_count();
	raw_spin_unlock_irqrestore(&erst_lock, flags);

	वापस count;
पूर्ण
EXPORT_SYMBOL_GPL(erst_get_record_count);

#घोषणा ERST_RECORD_ID_CACHE_SIZE_MIN	16
#घोषणा ERST_RECORD_ID_CACHE_SIZE_MAX	1024

काष्ठा erst_record_id_cache अणु
	काष्ठा mutex lock;
	u64 *entries;
	पूर्णांक len;
	पूर्णांक size;
	पूर्णांक refcount;
पूर्ण;

अटल काष्ठा erst_record_id_cache erst_record_id_cache = अणु
	.lock = __MUTEX_INITIALIZER(erst_record_id_cache.lock),
	.refcount = 0,
पूर्ण;

अटल पूर्णांक __erst_get_next_record_id(u64 *record_id)
अणु
	काष्ठा apei_exec_context ctx;
	पूर्णांक rc;

	erst_exec_ctx_init(&ctx);
	rc = apei_exec_run(&ctx, ACPI_ERST_GET_RECORD_ID);
	अगर (rc)
		वापस rc;
	*record_id = apei_exec_ctx_get_output(&ctx);

	वापस 0;
पूर्ण

पूर्णांक erst_get_record_id_begin(पूर्णांक *pos)
अणु
	पूर्णांक rc;

	अगर (erst_disable)
		वापस -ENODEV;

	rc = mutex_lock_पूर्णांकerruptible(&erst_record_id_cache.lock);
	अगर (rc)
		वापस rc;
	erst_record_id_cache.refcount++;
	mutex_unlock(&erst_record_id_cache.lock);

	*pos = 0;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(erst_get_record_id_begin);

/* erst_record_id_cache.lock must be held by caller */
अटल पूर्णांक __erst_record_id_cache_add_one(व्योम)
अणु
	u64 id, prev_id, first_id;
	पूर्णांक i, rc;
	u64 *entries;
	अचिन्हित दीर्घ flags;

	id = prev_id = first_id = APEI_ERST_INVALID_RECORD_ID;
retry:
	raw_spin_lock_irqsave(&erst_lock, flags);
	rc = __erst_get_next_record_id(&id);
	raw_spin_unlock_irqrestore(&erst_lock, flags);
	अगर (rc == -ENOENT)
		वापस 0;
	अगर (rc)
		वापस rc;
	अगर (id == APEI_ERST_INVALID_RECORD_ID)
		वापस 0;
	/* can not skip current ID, or loop back to first ID */
	अगर (id == prev_id || id == first_id)
		वापस 0;
	अगर (first_id == APEI_ERST_INVALID_RECORD_ID)
		first_id = id;
	prev_id = id;

	entries = erst_record_id_cache.entries;
	क्रम (i = 0; i < erst_record_id_cache.len; i++) अणु
		अगर (entries[i] == id)
			अवरोध;
	पूर्ण
	/* record id alपढ़ोy in cache, try next */
	अगर (i < erst_record_id_cache.len)
		जाओ retry;
	अगर (erst_record_id_cache.len >= erst_record_id_cache.size) अणु
		पूर्णांक new_size;
		u64 *new_entries;

		new_size = erst_record_id_cache.size * 2;
		new_size = clamp_val(new_size, ERST_RECORD_ID_CACHE_SIZE_MIN,
				     ERST_RECORD_ID_CACHE_SIZE_MAX);
		अगर (new_size <= erst_record_id_cache.size) अणु
			अगर (prपूर्णांकk_ratelimit())
				pr_warn(FW_WARN "too many record IDs!\n");
			वापस 0;
		पूर्ण
		new_entries = kvदो_स्मृति_array(new_size, माप(entries[0]),
					     GFP_KERNEL);
		अगर (!new_entries)
			वापस -ENOMEM;
		स_नकल(new_entries, entries,
		       erst_record_id_cache.len * माप(entries[0]));
		kvमुक्त(entries);
		erst_record_id_cache.entries = entries = new_entries;
		erst_record_id_cache.size = new_size;
	पूर्ण
	entries[i] = id;
	erst_record_id_cache.len++;

	वापस 1;
पूर्ण

/*
 * Get the record ID of an existing error record on the persistent
 * storage. If there is no error record on the persistent storage, the
 * वापसed record_id is APEI_ERST_INVALID_RECORD_ID.
 */
पूर्णांक erst_get_record_id_next(पूर्णांक *pos, u64 *record_id)
अणु
	पूर्णांक rc = 0;
	u64 *entries;

	अगर (erst_disable)
		वापस -ENODEV;

	/* must be enबंदd by erst_get_record_id_begin/end */
	BUG_ON(!erst_record_id_cache.refcount);
	BUG_ON(*pos < 0 || *pos > erst_record_id_cache.len);

	mutex_lock(&erst_record_id_cache.lock);
	entries = erst_record_id_cache.entries;
	क्रम (; *pos < erst_record_id_cache.len; (*pos)++)
		अगर (entries[*pos] != APEI_ERST_INVALID_RECORD_ID)
			अवरोध;
	/* found next record id in cache */
	अगर (*pos < erst_record_id_cache.len) अणु
		*record_id = entries[*pos];
		(*pos)++;
		जाओ out_unlock;
	पूर्ण

	/* Try to add one more record ID to cache */
	rc = __erst_record_id_cache_add_one();
	अगर (rc < 0)
		जाओ out_unlock;
	/* successfully add one new ID */
	अगर (rc == 1) अणु
		*record_id = erst_record_id_cache.entries[*pos];
		(*pos)++;
		rc = 0;
	पूर्ण अन्यथा अणु
		*pos = -1;
		*record_id = APEI_ERST_INVALID_RECORD_ID;
	पूर्ण
out_unlock:
	mutex_unlock(&erst_record_id_cache.lock);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(erst_get_record_id_next);

/* erst_record_id_cache.lock must be held by caller */
अटल व्योम __erst_record_id_cache_compact(व्योम)
अणु
	पूर्णांक i, wpos = 0;
	u64 *entries;

	अगर (erst_record_id_cache.refcount)
		वापस;

	entries = erst_record_id_cache.entries;
	क्रम (i = 0; i < erst_record_id_cache.len; i++) अणु
		अगर (entries[i] == APEI_ERST_INVALID_RECORD_ID)
			जारी;
		अगर (wpos != i)
			entries[wpos] = entries[i];
		wpos++;
	पूर्ण
	erst_record_id_cache.len = wpos;
पूर्ण

व्योम erst_get_record_id_end(व्योम)
अणु
	/*
	 * erst_disable != 0 should be detected by invoker via the
	 * वापस value of erst_get_record_id_begin/next, so this
	 * function should not be called क्रम erst_disable != 0.
	 */
	BUG_ON(erst_disable);

	mutex_lock(&erst_record_id_cache.lock);
	erst_record_id_cache.refcount--;
	BUG_ON(erst_record_id_cache.refcount < 0);
	__erst_record_id_cache_compact();
	mutex_unlock(&erst_record_id_cache.lock);
पूर्ण
EXPORT_SYMBOL_GPL(erst_get_record_id_end);

अटल पूर्णांक __erst_ग_लिखो_to_storage(u64 offset)
अणु
	काष्ठा apei_exec_context ctx;
	u64 समयout = FIRMWARE_TIMEOUT;
	u64 val;
	पूर्णांक rc;

	erst_exec_ctx_init(&ctx);
	rc = apei_exec_run_optional(&ctx, ACPI_ERST_BEGIN_WRITE);
	अगर (rc)
		वापस rc;
	apei_exec_ctx_set_input(&ctx, offset);
	rc = apei_exec_run(&ctx, ACPI_ERST_SET_RECORD_OFFSET);
	अगर (rc)
		वापस rc;
	rc = apei_exec_run(&ctx, ACPI_ERST_EXECUTE_OPERATION);
	अगर (rc)
		वापस rc;
	क्रम (;;) अणु
		rc = apei_exec_run(&ctx, ACPI_ERST_CHECK_BUSY_STATUS);
		अगर (rc)
			वापस rc;
		val = apei_exec_ctx_get_output(&ctx);
		अगर (!val)
			अवरोध;
		अगर (erst_समयकरोut(&समयout, SPIN_UNIT))
			वापस -EIO;
	पूर्ण
	rc = apei_exec_run(&ctx, ACPI_ERST_GET_COMMAND_STATUS);
	अगर (rc)
		वापस rc;
	val = apei_exec_ctx_get_output(&ctx);
	rc = apei_exec_run_optional(&ctx, ACPI_ERST_END);
	अगर (rc)
		वापस rc;

	वापस erst_त्रुटि_सं(val);
पूर्ण

अटल पूर्णांक __erst_पढ़ो_from_storage(u64 record_id, u64 offset)
अणु
	काष्ठा apei_exec_context ctx;
	u64 समयout = FIRMWARE_TIMEOUT;
	u64 val;
	पूर्णांक rc;

	erst_exec_ctx_init(&ctx);
	rc = apei_exec_run_optional(&ctx, ACPI_ERST_BEGIN_READ);
	अगर (rc)
		वापस rc;
	apei_exec_ctx_set_input(&ctx, offset);
	rc = apei_exec_run(&ctx, ACPI_ERST_SET_RECORD_OFFSET);
	अगर (rc)
		वापस rc;
	apei_exec_ctx_set_input(&ctx, record_id);
	rc = apei_exec_run(&ctx, ACPI_ERST_SET_RECORD_ID);
	अगर (rc)
		वापस rc;
	rc = apei_exec_run(&ctx, ACPI_ERST_EXECUTE_OPERATION);
	अगर (rc)
		वापस rc;
	क्रम (;;) अणु
		rc = apei_exec_run(&ctx, ACPI_ERST_CHECK_BUSY_STATUS);
		अगर (rc)
			वापस rc;
		val = apei_exec_ctx_get_output(&ctx);
		अगर (!val)
			अवरोध;
		अगर (erst_समयकरोut(&समयout, SPIN_UNIT))
			वापस -EIO;
	पूर्ण
	rc = apei_exec_run(&ctx, ACPI_ERST_GET_COMMAND_STATUS);
	अगर (rc)
		वापस rc;
	val = apei_exec_ctx_get_output(&ctx);
	rc = apei_exec_run_optional(&ctx, ACPI_ERST_END);
	अगर (rc)
		वापस rc;

	वापस erst_त्रुटि_सं(val);
पूर्ण

अटल पूर्णांक __erst_clear_from_storage(u64 record_id)
अणु
	काष्ठा apei_exec_context ctx;
	u64 समयout = FIRMWARE_TIMEOUT;
	u64 val;
	पूर्णांक rc;

	erst_exec_ctx_init(&ctx);
	rc = apei_exec_run_optional(&ctx, ACPI_ERST_BEGIN_CLEAR);
	अगर (rc)
		वापस rc;
	apei_exec_ctx_set_input(&ctx, record_id);
	rc = apei_exec_run(&ctx, ACPI_ERST_SET_RECORD_ID);
	अगर (rc)
		वापस rc;
	rc = apei_exec_run(&ctx, ACPI_ERST_EXECUTE_OPERATION);
	अगर (rc)
		वापस rc;
	क्रम (;;) अणु
		rc = apei_exec_run(&ctx, ACPI_ERST_CHECK_BUSY_STATUS);
		अगर (rc)
			वापस rc;
		val = apei_exec_ctx_get_output(&ctx);
		अगर (!val)
			अवरोध;
		अगर (erst_समयकरोut(&समयout, SPIN_UNIT))
			वापस -EIO;
	पूर्ण
	rc = apei_exec_run(&ctx, ACPI_ERST_GET_COMMAND_STATUS);
	अगर (rc)
		वापस rc;
	val = apei_exec_ctx_get_output(&ctx);
	rc = apei_exec_run_optional(&ctx, ACPI_ERST_END);
	अगर (rc)
		वापस rc;

	वापस erst_त्रुटि_सं(val);
पूर्ण

/* NVRAM ERST Error Log Address Range is not supported yet */
अटल व्योम pr_unimpl_nvram(व्योम)
अणु
	अगर (prपूर्णांकk_ratelimit())
		pr_warn("NVRAM ERST Log Address Range not implemented yet.\n");
पूर्ण

अटल पूर्णांक __erst_ग_लिखो_to_nvram(स्थिर काष्ठा cper_record_header *record)
अणु
	/* करो not prपूर्णांक message, because prपूर्णांकk is not safe क्रम NMI */
	वापस -ENOSYS;
पूर्ण

अटल पूर्णांक __erst_पढ़ो_to_erange_from_nvram(u64 record_id, u64 *offset)
अणु
	pr_unimpl_nvram();
	वापस -ENOSYS;
पूर्ण

अटल पूर्णांक __erst_clear_from_nvram(u64 record_id)
अणु
	pr_unimpl_nvram();
	वापस -ENOSYS;
पूर्ण

पूर्णांक erst_ग_लिखो(स्थिर काष्ठा cper_record_header *record)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ flags;
	काष्ठा cper_record_header *rcd_erange;

	अगर (erst_disable)
		वापस -ENODEV;

	अगर (स_भेद(record->signature, CPER_SIG_RECORD, CPER_SIG_SIZE))
		वापस -EINVAL;

	अगर (erst_erange.attr & ERST_RANGE_NVRAM) अणु
		अगर (!raw_spin_trylock_irqsave(&erst_lock, flags))
			वापस -EBUSY;
		rc = __erst_ग_लिखो_to_nvram(record);
		raw_spin_unlock_irqrestore(&erst_lock, flags);
		वापस rc;
	पूर्ण

	अगर (record->record_length > erst_erange.size)
		वापस -EINVAL;

	अगर (!raw_spin_trylock_irqsave(&erst_lock, flags))
		वापस -EBUSY;
	स_नकल(erst_erange.vaddr, record, record->record_length);
	rcd_erange = erst_erange.vaddr;
	/* signature क्रम serialization प्रणाली */
	स_नकल(&rcd_erange->persistence_inक्रमmation, "ER", 2);

	rc = __erst_ग_लिखो_to_storage(0);
	raw_spin_unlock_irqrestore(&erst_lock, flags);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(erst_ग_लिखो);

अटल पूर्णांक __erst_पढ़ो_to_erange(u64 record_id, u64 *offset)
अणु
	पूर्णांक rc;

	अगर (erst_erange.attr & ERST_RANGE_NVRAM)
		वापस __erst_पढ़ो_to_erange_from_nvram(
			record_id, offset);

	rc = __erst_पढ़ो_from_storage(record_id, 0);
	अगर (rc)
		वापस rc;
	*offset = 0;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार __erst_पढ़ो(u64 record_id, काष्ठा cper_record_header *record,
			   माप_प्रकार buflen)
अणु
	पूर्णांक rc;
	u64 offset, len = 0;
	काष्ठा cper_record_header *rcd_पंचांगp;

	rc = __erst_पढ़ो_to_erange(record_id, &offset);
	अगर (rc)
		वापस rc;
	rcd_पंचांगp = erst_erange.vaddr + offset;
	len = rcd_पंचांगp->record_length;
	अगर (len <= buflen)
		स_नकल(record, rcd_पंचांगp, len);

	वापस len;
पूर्ण

/*
 * If वापस value > buflen, the buffer size is not big enough,
 * अन्यथा अगर वापस value < 0, something goes wrong,
 * अन्यथा everything is OK, and वापस value is record length
 */
sमाप_प्रकार erst_पढ़ो(u64 record_id, काष्ठा cper_record_header *record,
		  माप_प्रकार buflen)
अणु
	sमाप_प्रकार len;
	अचिन्हित दीर्घ flags;

	अगर (erst_disable)
		वापस -ENODEV;

	raw_spin_lock_irqsave(&erst_lock, flags);
	len = __erst_पढ़ो(record_id, record, buflen);
	raw_spin_unlock_irqrestore(&erst_lock, flags);
	वापस len;
पूर्ण
EXPORT_SYMBOL_GPL(erst_पढ़ो);

पूर्णांक erst_clear(u64 record_id)
अणु
	पूर्णांक rc, i;
	अचिन्हित दीर्घ flags;
	u64 *entries;

	अगर (erst_disable)
		वापस -ENODEV;

	rc = mutex_lock_पूर्णांकerruptible(&erst_record_id_cache.lock);
	अगर (rc)
		वापस rc;
	raw_spin_lock_irqsave(&erst_lock, flags);
	अगर (erst_erange.attr & ERST_RANGE_NVRAM)
		rc = __erst_clear_from_nvram(record_id);
	अन्यथा
		rc = __erst_clear_from_storage(record_id);
	raw_spin_unlock_irqrestore(&erst_lock, flags);
	अगर (rc)
		जाओ out;
	entries = erst_record_id_cache.entries;
	क्रम (i = 0; i < erst_record_id_cache.len; i++) अणु
		अगर (entries[i] == record_id)
			entries[i] = APEI_ERST_INVALID_RECORD_ID;
	पूर्ण
	__erst_record_id_cache_compact();
out:
	mutex_unlock(&erst_record_id_cache.lock);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(erst_clear);

अटल पूर्णांक __init setup_erst_disable(अक्षर *str)
अणु
	erst_disable = 1;
	वापस 0;
पूर्ण

__setup("erst_disable", setup_erst_disable);

अटल पूर्णांक erst_check_table(काष्ठा acpi_table_erst *erst_tab)
अणु
	अगर ((erst_tab->header_length !=
	     (माप(काष्ठा acpi_table_erst) - माप(erst_tab->header)))
	    && (erst_tab->header_length != माप(काष्ठा acpi_table_erst)))
		वापस -EINVAL;
	अगर (erst_tab->header.length < माप(काष्ठा acpi_table_erst))
		वापस -EINVAL;
	अगर (erst_tab->entries !=
	    (erst_tab->header.length - माप(काष्ठा acpi_table_erst)) /
	    माप(काष्ठा acpi_erst_entry))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक erst_खोलो_pstore(काष्ठा pstore_info *psi);
अटल पूर्णांक erst_बंद_pstore(काष्ठा pstore_info *psi);
अटल sमाप_प्रकार erst_पढ़ोer(काष्ठा pstore_record *record);
अटल पूर्णांक erst_ग_लिखोr(काष्ठा pstore_record *record);
अटल पूर्णांक erst_clearer(काष्ठा pstore_record *record);

अटल काष्ठा pstore_info erst_info = अणु
	.owner		= THIS_MODULE,
	.name		= "erst",
	.flags		= PSTORE_FLAGS_DMESG,
	.खोलो		= erst_खोलो_pstore,
	.बंद		= erst_बंद_pstore,
	.पढ़ो		= erst_पढ़ोer,
	.ग_लिखो		= erst_ग_लिखोr,
	.erase		= erst_clearer
पूर्ण;

#घोषणा CPER_CREATOR_PSTORE						\
	GUID_INIT(0x75a574e3, 0x5052, 0x4b29, 0x8a, 0x8e, 0xbe, 0x2c,	\
		  0x64, 0x90, 0xb8, 0x9d)
#घोषणा CPER_SECTION_TYPE_DMESG						\
	GUID_INIT(0xc197e04e, 0xd545, 0x4a70, 0x9c, 0x17, 0xa5, 0x54,	\
		  0x94, 0x19, 0xeb, 0x12)
#घोषणा CPER_SECTION_TYPE_DMESG_Z					\
	GUID_INIT(0x4f118707, 0x04dd, 0x4055, 0xb5, 0xdd, 0x95, 0x6d,	\
		  0x34, 0xdd, 0xfa, 0xc6)
#घोषणा CPER_SECTION_TYPE_MCE						\
	GUID_INIT(0xfe08ffbe, 0x95e4, 0x4be7, 0xbc, 0x73, 0x40, 0x96,	\
		  0x04, 0x4a, 0x38, 0xfc)

काष्ठा cper_pstore_record अणु
	काष्ठा cper_record_header hdr;
	काष्ठा cper_section_descriptor sec_hdr;
	अक्षर data[];
पूर्ण __packed;

अटल पूर्णांक पढ़ोer_pos;

अटल पूर्णांक erst_खोलो_pstore(काष्ठा pstore_info *psi)
अणु
	पूर्णांक rc;

	अगर (erst_disable)
		वापस -ENODEV;

	rc = erst_get_record_id_begin(&पढ़ोer_pos);

	वापस rc;
पूर्ण

अटल पूर्णांक erst_बंद_pstore(काष्ठा pstore_info *psi)
अणु
	erst_get_record_id_end();

	वापस 0;
पूर्ण

अटल sमाप_प्रकार erst_पढ़ोer(काष्ठा pstore_record *record)
अणु
	पूर्णांक rc;
	sमाप_प्रकार len = 0;
	u64 record_id;
	काष्ठा cper_pstore_record *rcd;
	माप_प्रकार rcd_len = माप(*rcd) + erst_info.bufsize;

	अगर (erst_disable)
		वापस -ENODEV;

	rcd = kदो_स्मृति(rcd_len, GFP_KERNEL);
	अगर (!rcd) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण
skip:
	rc = erst_get_record_id_next(&पढ़ोer_pos, &record_id);
	अगर (rc)
		जाओ out;

	/* no more record */
	अगर (record_id == APEI_ERST_INVALID_RECORD_ID) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	len = erst_पढ़ो(record_id, &rcd->hdr, rcd_len);
	/* The record may be cleared by others, try पढ़ो next record */
	अगर (len == -ENOENT)
		जाओ skip;
	अन्यथा अगर (len < 0 || len < माप(*rcd)) अणु
		rc = -EIO;
		जाओ out;
	पूर्ण
	अगर (!guid_equal(&rcd->hdr.creator_id, &CPER_CREATOR_PSTORE))
		जाओ skip;

	record->buf = kदो_स्मृति(len, GFP_KERNEL);
	अगर (record->buf == शून्य) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण
	स_नकल(record->buf, rcd->data, len - माप(*rcd));
	record->id = record_id;
	record->compressed = false;
	record->ecc_notice_size = 0;
	अगर (guid_equal(&rcd->sec_hdr.section_type, &CPER_SECTION_TYPE_DMESG_Z)) अणु
		record->type = PSTORE_TYPE_DMESG;
		record->compressed = true;
	पूर्ण अन्यथा अगर (guid_equal(&rcd->sec_hdr.section_type, &CPER_SECTION_TYPE_DMESG))
		record->type = PSTORE_TYPE_DMESG;
	अन्यथा अगर (guid_equal(&rcd->sec_hdr.section_type, &CPER_SECTION_TYPE_MCE))
		record->type = PSTORE_TYPE_MCE;
	अन्यथा
		record->type = PSTORE_TYPE_MAX;

	अगर (rcd->hdr.validation_bits & CPER_VALID_TIMESTAMP)
		record->समय.tv_sec = rcd->hdr.बारtamp;
	अन्यथा
		record->समय.tv_sec = 0;
	record->समय.tv_nsec = 0;

out:
	kमुक्त(rcd);
	वापस (rc < 0) ? rc : (len - माप(*rcd));
पूर्ण

अटल पूर्णांक erst_ग_लिखोr(काष्ठा pstore_record *record)
अणु
	काष्ठा cper_pstore_record *rcd = (काष्ठा cper_pstore_record *)
					(erst_info.buf - माप(*rcd));
	पूर्णांक ret;

	स_रखो(rcd, 0, माप(*rcd));
	स_नकल(rcd->hdr.signature, CPER_SIG_RECORD, CPER_SIG_SIZE);
	rcd->hdr.revision = CPER_RECORD_REV;
	rcd->hdr.signature_end = CPER_SIG_END;
	rcd->hdr.section_count = 1;
	rcd->hdr.error_severity = CPER_SEV_FATAL;
	/* बारtamp valid. platक्रमm_id, partition_id are invalid */
	rcd->hdr.validation_bits = CPER_VALID_TIMESTAMP;
	rcd->hdr.बारtamp = kसमय_get_real_seconds();
	rcd->hdr.record_length = माप(*rcd) + record->size;
	rcd->hdr.creator_id = CPER_CREATOR_PSTORE;
	rcd->hdr.notअगरication_type = CPER_NOTIFY_MCE;
	rcd->hdr.record_id = cper_next_record_id();
	rcd->hdr.flags = CPER_HW_ERROR_FLAGS_PREVERR;

	rcd->sec_hdr.section_offset = माप(*rcd);
	rcd->sec_hdr.section_length = record->size;
	rcd->sec_hdr.revision = CPER_SEC_REV;
	/* fru_id and fru_text is invalid */
	rcd->sec_hdr.validation_bits = 0;
	rcd->sec_hdr.flags = CPER_SEC_PRIMARY;
	चयन (record->type) अणु
	हाल PSTORE_TYPE_DMESG:
		अगर (record->compressed)
			rcd->sec_hdr.section_type = CPER_SECTION_TYPE_DMESG_Z;
		अन्यथा
			rcd->sec_hdr.section_type = CPER_SECTION_TYPE_DMESG;
		अवरोध;
	हाल PSTORE_TYPE_MCE:
		rcd->sec_hdr.section_type = CPER_SECTION_TYPE_MCE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	rcd->sec_hdr.section_severity = CPER_SEV_FATAL;

	ret = erst_ग_लिखो(&rcd->hdr);
	record->id = rcd->hdr.record_id;

	वापस ret;
पूर्ण

अटल पूर्णांक erst_clearer(काष्ठा pstore_record *record)
अणु
	वापस erst_clear(record->id);
पूर्ण

अटल पूर्णांक __init erst_init(व्योम)
अणु
	पूर्णांक rc = 0;
	acpi_status status;
	काष्ठा apei_exec_context ctx;
	काष्ठा apei_resources erst_resources;
	काष्ठा resource *r;
	अक्षर *buf;

	अगर (acpi_disabled)
		जाओ err;

	अगर (erst_disable) अणु
		pr_info(
	"Error Record Serialization Table (ERST) support is disabled.\n");
		जाओ err;
	पूर्ण

	status = acpi_get_table(ACPI_SIG_ERST, 0,
				(काष्ठा acpi_table_header **)&erst_tab);
	अगर (status == AE_NOT_FOUND)
		जाओ err;
	अन्यथा अगर (ACPI_FAILURE(status)) अणु
		स्थिर अक्षर *msg = acpi_क्रमmat_exception(status);
		pr_err("Failed to get table, %s\n", msg);
		rc = -EINVAL;
		जाओ err;
	पूर्ण

	rc = erst_check_table(erst_tab);
	अगर (rc) अणु
		pr_err(FW_BUG "ERST table is invalid.\n");
		जाओ err_put_erst_tab;
	पूर्ण

	apei_resources_init(&erst_resources);
	erst_exec_ctx_init(&ctx);
	rc = apei_exec_collect_resources(&ctx, &erst_resources);
	अगर (rc)
		जाओ err_fini;
	rc = apei_resources_request(&erst_resources, "APEI ERST");
	अगर (rc)
		जाओ err_fini;
	rc = apei_exec_pre_map_gars(&ctx);
	अगर (rc)
		जाओ err_release;
	rc = erst_get_erange(&erst_erange);
	अगर (rc) अणु
		अगर (rc == -ENODEV)
			pr_info(
	"The corresponding hardware device or firmware implementation "
	"is not available.\n");
		अन्यथा
			pr_err("Failed to get Error Log Address Range.\n");
		जाओ err_unmap_reg;
	पूर्ण

	r = request_mem_region(erst_erange.base, erst_erange.size, "APEI ERST");
	अगर (!r) अणु
		pr_err("Can not request [mem %#010llx-%#010llx] for ERST.\n",
		       (अचिन्हित दीर्घ दीर्घ)erst_erange.base,
		       (अचिन्हित दीर्घ दीर्घ)erst_erange.base + erst_erange.size - 1);
		rc = -EIO;
		जाओ err_unmap_reg;
	पूर्ण
	rc = -ENOMEM;
	erst_erange.vaddr = ioremap_cache(erst_erange.base,
					  erst_erange.size);
	अगर (!erst_erange.vaddr)
		जाओ err_release_erange;

	pr_info(
	"Error Record Serialization Table (ERST) support is initialized.\n");

	buf = kदो_स्मृति(erst_erange.size, GFP_KERNEL);
	अगर (buf) अणु
		erst_info.buf = buf + माप(काष्ठा cper_pstore_record);
		erst_info.bufsize = erst_erange.size -
				    माप(काष्ठा cper_pstore_record);
		rc = pstore_रेजिस्टर(&erst_info);
		अगर (rc) अणु
			अगर (rc != -EPERM)
				pr_info(
				"Could not register with persistent store.\n");
			erst_info.buf = शून्य;
			erst_info.bufsize = 0;
			kमुक्त(buf);
		पूर्ण
	पूर्ण अन्यथा
		pr_err(
		"Failed to allocate %lld bytes for persistent store error log.\n",
		erst_erange.size);

	/* Cleanup ERST Resources */
	apei_resources_fini(&erst_resources);

	वापस 0;

err_release_erange:
	release_mem_region(erst_erange.base, erst_erange.size);
err_unmap_reg:
	apei_exec_post_unmap_gars(&ctx);
err_release:
	apei_resources_release(&erst_resources);
err_fini:
	apei_resources_fini(&erst_resources);
err_put_erst_tab:
	acpi_put_table((काष्ठा acpi_table_header *)erst_tab);
err:
	erst_disable = 1;
	वापस rc;
पूर्ण

device_initcall(erst_init);

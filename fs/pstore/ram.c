<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * RAM Oops/Panic logger
 *
 * Copyright (C) 2010 Marco Stornelli <marco.stornelli@gmail.com>
 * Copyright (C) 2011 Kees Cook <keescook@chromium.org>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/version.h>
#समावेश <linux/pstore.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/compiler.h>
#समावेश <linux/pstore_ram.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश "internal.h"

#घोषणा RAMOOPS_KERNMSG_HDR "===="
#घोषणा MIN_MEM_SIZE 4096UL

अटल uदीर्घ record_size = MIN_MEM_SIZE;
module_param(record_size, uदीर्घ, 0400);
MODULE_PARM_DESC(record_size,
		"size of each dump done on oops/panic");

अटल uदीर्घ ramoops_console_size = MIN_MEM_SIZE;
module_param_named(console_size, ramoops_console_size, uदीर्घ, 0400);
MODULE_PARM_DESC(console_size, "size of kernel console log");

अटल uदीर्घ ramoops_ftrace_size = MIN_MEM_SIZE;
module_param_named(ftrace_size, ramoops_ftrace_size, uदीर्घ, 0400);
MODULE_PARM_DESC(ftrace_size, "size of ftrace log");

अटल uदीर्घ ramoops_pmsg_size = MIN_MEM_SIZE;
module_param_named(pmsg_size, ramoops_pmsg_size, uदीर्घ, 0400);
MODULE_PARM_DESC(pmsg_size, "size of user space message log");

अटल अचिन्हित दीर्घ दीर्घ mem_address;
module_param_hw(mem_address, ulदीर्घ, other, 0400);
MODULE_PARM_DESC(mem_address,
		"start of reserved RAM used to store oops/panic logs");

अटल uदीर्घ mem_size;
module_param(mem_size, uदीर्घ, 0400);
MODULE_PARM_DESC(mem_size,
		"size of reserved RAM used to store oops/panic logs");

अटल अचिन्हित पूर्णांक mem_type;
module_param(mem_type, uपूर्णांक, 0400);
MODULE_PARM_DESC(mem_type,
		"memory type: 0=write-combined (default), 1=unbuffered, 2=cached");

अटल पूर्णांक ramoops_max_reason = -1;
module_param_named(max_reason, ramoops_max_reason, पूर्णांक, 0400);
MODULE_PARM_DESC(max_reason,
		 "maximum reason for kmsg dump (default 2: Oops and Panic) ");

अटल पूर्णांक ramoops_ecc;
module_param_named(ecc, ramoops_ecc, पूर्णांक, 0400);
MODULE_PARM_DESC(ramoops_ecc,
		"if non-zero, the option enables ECC support and specifies "
		"ECC buffer size in bytes (1 is a special value, means 16 "
		"bytes ECC)");

अटल पूर्णांक ramoops_dump_oops = -1;
module_param_named(dump_oops, ramoops_dump_oops, पूर्णांक, 0400);
MODULE_PARM_DESC(dump_oops,
		 "(deprecated: use max_reason instead) set to 1 to dump oopses & panics, 0 to only dump panics");

काष्ठा ramoops_context अणु
	काष्ठा persistent_ram_zone **dprzs;	/* Oops dump zones */
	काष्ठा persistent_ram_zone *cprz;	/* Console zone */
	काष्ठा persistent_ram_zone **fprzs;	/* Ftrace zones */
	काष्ठा persistent_ram_zone *mprz;	/* PMSG zone */
	phys_addr_t phys_addr;
	अचिन्हित दीर्घ size;
	अचिन्हित पूर्णांक memtype;
	माप_प्रकार record_size;
	माप_प्रकार console_size;
	माप_प्रकार ftrace_size;
	माप_प्रकार pmsg_size;
	u32 flags;
	काष्ठा persistent_ram_ecc_info ecc_info;
	अचिन्हित पूर्णांक max_dump_cnt;
	अचिन्हित पूर्णांक dump_ग_लिखो_cnt;
	/* _पढ़ो_cnt need clear on ramoops_pstore_खोलो */
	अचिन्हित पूर्णांक dump_पढ़ो_cnt;
	अचिन्हित पूर्णांक console_पढ़ो_cnt;
	अचिन्हित पूर्णांक max_ftrace_cnt;
	अचिन्हित पूर्णांक ftrace_पढ़ो_cnt;
	अचिन्हित पूर्णांक pmsg_पढ़ो_cnt;
	काष्ठा pstore_info pstore;
पूर्ण;

अटल काष्ठा platक्रमm_device *dummy;

अटल पूर्णांक ramoops_pstore_खोलो(काष्ठा pstore_info *psi)
अणु
	काष्ठा ramoops_context *cxt = psi->data;

	cxt->dump_पढ़ो_cnt = 0;
	cxt->console_पढ़ो_cnt = 0;
	cxt->ftrace_पढ़ो_cnt = 0;
	cxt->pmsg_पढ़ो_cnt = 0;
	वापस 0;
पूर्ण

अटल काष्ठा persistent_ram_zone *
ramoops_get_next_prz(काष्ठा persistent_ram_zone *przs[], पूर्णांक id,
		     काष्ठा pstore_record *record)
अणु
	काष्ठा persistent_ram_zone *prz;

	/* Give up अगर we never existed or have hit the end. */
	अगर (!przs)
		वापस शून्य;

	prz = przs[id];
	अगर (!prz)
		वापस शून्य;

	/* Update old/shaकरोwed buffer. */
	अगर (prz->type == PSTORE_TYPE_DMESG)
		persistent_ram_save_old(prz);

	अगर (!persistent_ram_old_size(prz))
		वापस शून्य;

	record->type = prz->type;
	record->id = id;

	वापस prz;
पूर्ण

अटल पूर्णांक ramoops_पढ़ो_kmsg_hdr(अक्षर *buffer, काष्ठा बारpec64 *समय,
				  bool *compressed)
अणु
	अक्षर data_type;
	पूर्णांक header_length = 0;

	अगर (माला_पूछो(buffer, RAMOOPS_KERNMSG_HDR "%lld.%lu-%c\n%n",
		   (समय64_t *)&समय->tv_sec, &समय->tv_nsec, &data_type,
		   &header_length) == 3) अणु
		समय->tv_nsec *= 1000;
		अगर (data_type == 'C')
			*compressed = true;
		अन्यथा
			*compressed = false;
	पूर्ण अन्यथा अगर (माला_पूछो(buffer, RAMOOPS_KERNMSG_HDR "%lld.%lu\n%n",
			  (समय64_t *)&समय->tv_sec, &समय->tv_nsec,
			  &header_length) == 2) अणु
		समय->tv_nsec *= 1000;
		*compressed = false;
	पूर्ण अन्यथा अणु
		समय->tv_sec = 0;
		समय->tv_nsec = 0;
		*compressed = false;
	पूर्ण
	वापस header_length;
पूर्ण

अटल bool prz_ok(काष्ठा persistent_ram_zone *prz)
अणु
	वापस !!prz && !!(persistent_ram_old_size(prz) +
			   persistent_ram_ecc_string(prz, शून्य, 0));
पूर्ण

अटल sमाप_प्रकार ramoops_pstore_पढ़ो(काष्ठा pstore_record *record)
अणु
	sमाप_प्रकार size = 0;
	काष्ठा ramoops_context *cxt = record->psi->data;
	काष्ठा persistent_ram_zone *prz = शून्य;
	पूर्णांक header_length = 0;
	bool मुक्त_prz = false;

	/*
	 * Ramoops headers provide समय stamps क्रम PSTORE_TYPE_DMESG, but
	 * PSTORE_TYPE_CONSOLE and PSTORE_TYPE_FTRACE करोn't currently have
	 * valid समय stamps, so it is initialized to zero.
	 */
	record->समय.tv_sec = 0;
	record->समय.tv_nsec = 0;
	record->compressed = false;

	/* Find the next valid persistent_ram_zone क्रम DMESG */
	जबतक (cxt->dump_पढ़ो_cnt < cxt->max_dump_cnt && !prz) अणु
		prz = ramoops_get_next_prz(cxt->dprzs, cxt->dump_पढ़ो_cnt++,
					   record);
		अगर (!prz_ok(prz))
			जारी;
		header_length = ramoops_पढ़ो_kmsg_hdr(persistent_ram_old(prz),
						      &record->समय,
						      &record->compressed);
		/* Clear and skip this DMESG record अगर it has no valid header */
		अगर (!header_length) अणु
			persistent_ram_मुक्त_old(prz);
			persistent_ram_zap(prz);
			prz = शून्य;
		पूर्ण
	पूर्ण

	अगर (!prz_ok(prz) && !cxt->console_पढ़ो_cnt++)
		prz = ramoops_get_next_prz(&cxt->cprz, 0 /* single */, record);

	अगर (!prz_ok(prz) && !cxt->pmsg_पढ़ो_cnt++)
		prz = ramoops_get_next_prz(&cxt->mprz, 0 /* single */, record);

	/* ftrace is last since it may want to dynamically allocate memory. */
	अगर (!prz_ok(prz)) अणु
		अगर (!(cxt->flags & RAMOOPS_FLAG_FTRACE_PER_CPU) &&
		    !cxt->ftrace_पढ़ो_cnt++) अणु
			prz = ramoops_get_next_prz(cxt->fprzs, 0 /* single */,
						   record);
		पूर्ण अन्यथा अणु
			/*
			 * Build a new dummy record which combines all the
			 * per-cpu records including metadata and ecc info.
			 */
			काष्ठा persistent_ram_zone *पंचांगp_prz, *prz_next;

			पंचांगp_prz = kzalloc(माप(काष्ठा persistent_ram_zone),
					  GFP_KERNEL);
			अगर (!पंचांगp_prz)
				वापस -ENOMEM;
			prz = पंचांगp_prz;
			मुक्त_prz = true;

			जबतक (cxt->ftrace_पढ़ो_cnt < cxt->max_ftrace_cnt) अणु
				prz_next = ramoops_get_next_prz(cxt->fprzs,
						cxt->ftrace_पढ़ो_cnt++, record);

				अगर (!prz_ok(prz_next))
					जारी;

				पंचांगp_prz->ecc_info = prz_next->ecc_info;
				पंचांगp_prz->corrected_bytes +=
						prz_next->corrected_bytes;
				पंचांगp_prz->bad_blocks += prz_next->bad_blocks;

				size = pstore_ftrace_combine_log(
						&पंचांगp_prz->old_log,
						&पंचांगp_prz->old_log_size,
						prz_next->old_log,
						prz_next->old_log_size);
				अगर (size)
					जाओ out;
			पूर्ण
			record->id = 0;
		पूर्ण
	पूर्ण

	अगर (!prz_ok(prz)) अणु
		size = 0;
		जाओ out;
	पूर्ण

	size = persistent_ram_old_size(prz) - header_length;

	/* ECC correction notice */
	record->ecc_notice_size = persistent_ram_ecc_string(prz, शून्य, 0);

	record->buf = kदो_स्मृति(size + record->ecc_notice_size + 1, GFP_KERNEL);
	अगर (record->buf == शून्य) अणु
		size = -ENOMEM;
		जाओ out;
	पूर्ण

	स_नकल(record->buf, (अक्षर *)persistent_ram_old(prz) + header_length,
	       size);

	persistent_ram_ecc_string(prz, record->buf + size,
				  record->ecc_notice_size + 1);

out:
	अगर (मुक्त_prz) अणु
		kमुक्त(prz->old_log);
		kमुक्त(prz);
	पूर्ण

	वापस size;
पूर्ण

अटल माप_प्रकार ramoops_ग_लिखो_kmsg_hdr(काष्ठा persistent_ram_zone *prz,
				     काष्ठा pstore_record *record)
अणु
	अक्षर hdr[36]; /* "===="(4), %lld(20), "."(1), %06lu(6), "-%c\n"(3) */
	माप_प्रकार len;

	len = scnम_लिखो(hdr, माप(hdr),
		RAMOOPS_KERNMSG_HDR "%lld.%06lu-%c\n",
		(समय64_t)record->समय.tv_sec,
		record->समय.tv_nsec / 1000,
		record->compressed ? 'C' : 'D');
	persistent_ram_ग_लिखो(prz, hdr, len);

	वापस len;
पूर्ण

अटल पूर्णांक notrace ramoops_pstore_ग_लिखो(काष्ठा pstore_record *record)
अणु
	काष्ठा ramoops_context *cxt = record->psi->data;
	काष्ठा persistent_ram_zone *prz;
	माप_प्रकार size, hlen;

	अगर (record->type == PSTORE_TYPE_CONSOLE) अणु
		अगर (!cxt->cprz)
			वापस -ENOMEM;
		persistent_ram_ग_लिखो(cxt->cprz, record->buf, record->size);
		वापस 0;
	पूर्ण अन्यथा अगर (record->type == PSTORE_TYPE_FTRACE) अणु
		पूर्णांक zonक्रमागत;

		अगर (!cxt->fprzs)
			वापस -ENOMEM;
		/*
		 * Choose zone by अगर we're using per-cpu buffers.
		 */
		अगर (cxt->flags & RAMOOPS_FLAG_FTRACE_PER_CPU)
			zonक्रमागत = smp_processor_id();
		अन्यथा
			zonक्रमागत = 0;

		persistent_ram_ग_लिखो(cxt->fprzs[zonक्रमागत], record->buf,
				     record->size);
		वापस 0;
	पूर्ण अन्यथा अगर (record->type == PSTORE_TYPE_PMSG) अणु
		pr_warn_ratelimited("PMSG shouldn't call %s\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (record->type != PSTORE_TYPE_DMESG)
		वापस -EINVAL;

	/*
	 * We could filter on record->reason here अगर we wanted to (which
	 * would duplicate what happened beक्रमe the "max_reason" setting
	 * was added), but that would defeat the purpose of a प्रणाली
	 * changing prपूर्णांकk.always_kmsg_dump, so instead log everything that
	 * the kmsg dumper sends us, since it should be करोing the filtering
	 * based on the combination of prपूर्णांकk.always_kmsg_dump and our
	 * requested "max_reason".
	 */

	/*
	 * Explicitly only take the first part of any new crash.
	 * If our buffer is larger than kmsg_bytes, this can never happen,
	 * and अगर our buffer is smaller than kmsg_bytes, we करोn't want the
	 * report split across multiple records.
	 */
	अगर (record->part != 1)
		वापस -ENOSPC;

	अगर (!cxt->dprzs)
		वापस -ENOSPC;

	prz = cxt->dprzs[cxt->dump_ग_लिखो_cnt];

	/*
	 * Since this is a new crash dump, we need to reset the buffer in
	 * हाल it still has an old dump present. Without this, the new dump
	 * will get appended, which would seriously confuse anything trying
	 * to check dump file contents. Specअगरically, ramoops_पढ़ो_kmsg_hdr()
	 * expects to find a dump header in the beginning of buffer data, so
	 * we must to reset the buffer values, in order to ensure that the
	 * header will be written to the beginning of the buffer.
	 */
	persistent_ram_zap(prz);

	/* Build header and append record contents. */
	hlen = ramoops_ग_लिखो_kmsg_hdr(prz, record);
	अगर (!hlen)
		वापस -ENOMEM;

	size = record->size;
	अगर (size + hlen > prz->buffer_size)
		size = prz->buffer_size - hlen;
	persistent_ram_ग_लिखो(prz, record->buf, size);

	cxt->dump_ग_लिखो_cnt = (cxt->dump_ग_लिखो_cnt + 1) % cxt->max_dump_cnt;

	वापस 0;
पूर्ण

अटल पूर्णांक notrace ramoops_pstore_ग_लिखो_user(काष्ठा pstore_record *record,
					     स्थिर अक्षर __user *buf)
अणु
	अगर (record->type == PSTORE_TYPE_PMSG) अणु
		काष्ठा ramoops_context *cxt = record->psi->data;

		अगर (!cxt->mprz)
			वापस -ENOMEM;
		वापस persistent_ram_ग_लिखो_user(cxt->mprz, buf, record->size);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ramoops_pstore_erase(काष्ठा pstore_record *record)
अणु
	काष्ठा ramoops_context *cxt = record->psi->data;
	काष्ठा persistent_ram_zone *prz;

	चयन (record->type) अणु
	हाल PSTORE_TYPE_DMESG:
		अगर (record->id >= cxt->max_dump_cnt)
			वापस -EINVAL;
		prz = cxt->dprzs[record->id];
		अवरोध;
	हाल PSTORE_TYPE_CONSOLE:
		prz = cxt->cprz;
		अवरोध;
	हाल PSTORE_TYPE_FTRACE:
		अगर (record->id >= cxt->max_ftrace_cnt)
			वापस -EINVAL;
		prz = cxt->fprzs[record->id];
		अवरोध;
	हाल PSTORE_TYPE_PMSG:
		prz = cxt->mprz;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	persistent_ram_मुक्त_old(prz);
	persistent_ram_zap(prz);

	वापस 0;
पूर्ण

अटल काष्ठा ramoops_context oops_cxt = अणु
	.pstore = अणु
		.owner	= THIS_MODULE,
		.name	= "ramoops",
		.खोलो	= ramoops_pstore_खोलो,
		.पढ़ो	= ramoops_pstore_पढ़ो,
		.ग_लिखो	= ramoops_pstore_ग_लिखो,
		.ग_लिखो_user	= ramoops_pstore_ग_लिखो_user,
		.erase	= ramoops_pstore_erase,
	पूर्ण,
पूर्ण;

अटल व्योम ramoops_मुक्त_przs(काष्ठा ramoops_context *cxt)
अणु
	पूर्णांक i;

	/* Free dump PRZs */
	अगर (cxt->dprzs) अणु
		क्रम (i = 0; i < cxt->max_dump_cnt; i++)
			persistent_ram_मुक्त(cxt->dprzs[i]);

		kमुक्त(cxt->dprzs);
		cxt->max_dump_cnt = 0;
	पूर्ण

	/* Free ftrace PRZs */
	अगर (cxt->fprzs) अणु
		क्रम (i = 0; i < cxt->max_ftrace_cnt; i++)
			persistent_ram_मुक्त(cxt->fprzs[i]);
		kमुक्त(cxt->fprzs);
		cxt->max_ftrace_cnt = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक ramoops_init_przs(स्थिर अक्षर *name,
			     काष्ठा device *dev, काष्ठा ramoops_context *cxt,
			     काष्ठा persistent_ram_zone ***przs,
			     phys_addr_t *paddr, माप_प्रकार mem_sz,
			     sमाप_प्रकार record_size,
			     अचिन्हित पूर्णांक *cnt, u32 sig, u32 flags)
अणु
	पूर्णांक err = -ENOMEM;
	पूर्णांक i;
	माप_प्रकार zone_sz;
	काष्ठा persistent_ram_zone **prz_ar;

	/* Allocate nothing क्रम 0 mem_sz or 0 record_size. */
	अगर (mem_sz == 0 || record_size == 0) अणु
		*cnt = 0;
		वापस 0;
	पूर्ण

	/*
	 * If we have a negative record size, calculate it based on
	 * mem_sz / *cnt. If we have a positive record size, calculate
	 * cnt from mem_sz / record_size.
	 */
	अगर (record_size < 0) अणु
		अगर (*cnt == 0)
			वापस 0;
		record_size = mem_sz / *cnt;
		अगर (record_size == 0) अणु
			dev_err(dev, "%s record size == 0 (%zu / %u)\n",
				name, mem_sz, *cnt);
			जाओ fail;
		पूर्ण
	पूर्ण अन्यथा अणु
		*cnt = mem_sz / record_size;
		अगर (*cnt == 0) अणु
			dev_err(dev, "%s record count == 0 (%zu / %zu)\n",
				name, mem_sz, record_size);
			जाओ fail;
		पूर्ण
	पूर्ण

	अगर (*paddr + mem_sz - cxt->phys_addr > cxt->size) अणु
		dev_err(dev, "no room for %s mem region (0x%zx@0x%llx) in (0x%lx@0x%llx)\n",
			name,
			mem_sz, (अचिन्हित दीर्घ दीर्घ)*paddr,
			cxt->size, (अचिन्हित दीर्घ दीर्घ)cxt->phys_addr);
		जाओ fail;
	पूर्ण

	zone_sz = mem_sz / *cnt;
	अगर (!zone_sz) अणु
		dev_err(dev, "%s zone size == 0\n", name);
		जाओ fail;
	पूर्ण

	prz_ar = kसुस्मृति(*cnt, माप(**przs), GFP_KERNEL);
	अगर (!prz_ar)
		जाओ fail;

	क्रम (i = 0; i < *cnt; i++) अणु
		अक्षर *label;

		अगर (*cnt == 1)
			label = kaप्र_लिखो(GFP_KERNEL, "ramoops:%s", name);
		अन्यथा
			label = kaप्र_लिखो(GFP_KERNEL, "ramoops:%s(%d/%d)",
					  name, i, *cnt - 1);
		prz_ar[i] = persistent_ram_new(*paddr, zone_sz, sig,
					       &cxt->ecc_info,
					       cxt->memtype, flags, label);
		kमुक्त(label);
		अगर (IS_ERR(prz_ar[i])) अणु
			err = PTR_ERR(prz_ar[i]);
			dev_err(dev, "failed to request %s mem region (0x%zx@0x%llx): %d\n",
				name, record_size,
				(अचिन्हित दीर्घ दीर्घ)*paddr, err);

			जबतक (i > 0) अणु
				i--;
				persistent_ram_मुक्त(prz_ar[i]);
			पूर्ण
			kमुक्त(prz_ar);
			जाओ fail;
		पूर्ण
		*paddr += zone_sz;
		prz_ar[i]->type = pstore_name_to_type(name);
	पूर्ण

	*przs = prz_ar;
	वापस 0;

fail:
	*cnt = 0;
	वापस err;
पूर्ण

अटल पूर्णांक ramoops_init_prz(स्थिर अक्षर *name,
			    काष्ठा device *dev, काष्ठा ramoops_context *cxt,
			    काष्ठा persistent_ram_zone **prz,
			    phys_addr_t *paddr, माप_प्रकार sz, u32 sig)
अणु
	अक्षर *label;

	अगर (!sz)
		वापस 0;

	अगर (*paddr + sz - cxt->phys_addr > cxt->size) अणु
		dev_err(dev, "no room for %s mem region (0x%zx@0x%llx) in (0x%lx@0x%llx)\n",
			name, sz, (अचिन्हित दीर्घ दीर्घ)*paddr,
			cxt->size, (अचिन्हित दीर्घ दीर्घ)cxt->phys_addr);
		वापस -ENOMEM;
	पूर्ण

	label = kaप्र_लिखो(GFP_KERNEL, "ramoops:%s", name);
	*prz = persistent_ram_new(*paddr, sz, sig, &cxt->ecc_info,
				  cxt->memtype, PRZ_FLAG_ZAP_OLD, label);
	kमुक्त(label);
	अगर (IS_ERR(*prz)) अणु
		पूर्णांक err = PTR_ERR(*prz);

		dev_err(dev, "failed to request %s mem region (0x%zx@0x%llx): %d\n",
			name, sz, (अचिन्हित दीर्घ दीर्घ)*paddr, err);
		वापस err;
	पूर्ण

	*paddr += sz;
	(*prz)->type = pstore_name_to_type(name);

	वापस 0;
पूर्ण

/* Read a u32 from a dt property and make sure it's safe क्रम an पूर्णांक. */
अटल पूर्णांक ramoops_parse_dt_u32(काष्ठा platक्रमm_device *pdev,
				स्थिर अक्षर *propname,
				u32 शेष_value, u32 *value)
अणु
	u32 val32 = 0;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32(pdev->dev.of_node, propname, &val32);
	अगर (ret == -EINVAL) अणु
		/* field is missing, use शेष value. */
		val32 = शेष_value;
	पूर्ण अन्यथा अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to parse property %s: %d\n",
			propname, ret);
		वापस ret;
	पूर्ण

	/* Sanity check our results. */
	अगर (val32 > पूर्णांक_उच्च) अणु
		dev_err(&pdev->dev, "%s %u > INT_MAX\n", propname, val32);
		वापस -EOVERFLOW;
	पूर्ण

	*value = val32;
	वापस 0;
पूर्ण

अटल पूर्णांक ramoops_parse_dt(काष्ठा platक्रमm_device *pdev,
			    काष्ठा ramoops_platक्रमm_data *pdata)
अणु
	काष्ठा device_node *of_node = pdev->dev.of_node;
	काष्ठा device_node *parent_node;
	काष्ठा resource *res;
	u32 value;
	पूर्णांक ret;

	dev_dbg(&pdev->dev, "using Device Tree\n");

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev,
			"failed to locate DT /reserved-memory resource\n");
		वापस -EINVAL;
	पूर्ण

	pdata->mem_size = resource_size(res);
	pdata->mem_address = res->start;
	/*
	 * Setting "unbuffered" is deprecated and will be ignored अगर
	 * "mem_type" is also specअगरied.
	 */
	pdata->mem_type = of_property_पढ़ो_bool(of_node, "unbuffered");
	/*
	 * Setting "no-dump-oops" is deprecated and will be ignored अगर
	 * "max_reason" is also specअगरied.
	 */
	अगर (of_property_पढ़ो_bool(of_node, "no-dump-oops"))
		pdata->max_reason = KMSG_DUMP_PANIC;
	अन्यथा
		pdata->max_reason = KMSG_DUMP_OOPS;

#घोषणा parse_u32(name, field, शेष_value) अणु				\
		ret = ramoops_parse_dt_u32(pdev, name, शेष_value,	\
					    &value);			\
		अगर (ret < 0)						\
			वापस ret;					\
		field = value;						\
	पूर्ण

	parse_u32("mem-type", pdata->record_size, pdata->mem_type);
	parse_u32("record-size", pdata->record_size, 0);
	parse_u32("console-size", pdata->console_size, 0);
	parse_u32("ftrace-size", pdata->ftrace_size, 0);
	parse_u32("pmsg-size", pdata->pmsg_size, 0);
	parse_u32("ecc-size", pdata->ecc_info.ecc_size, 0);
	parse_u32("flags", pdata->flags, 0);
	parse_u32("max-reason", pdata->max_reason, pdata->max_reason);

#अघोषित parse_u32

	/*
	 * Some old Chromebooks relied on the kernel setting the
	 * console_size and pmsg_size to the record size since that's
	 * what the करोwnstream kernel did.  These same Chromebooks had
	 * "ramoops" straight under the root node which isn't
	 * according to the current upstream bindings (though it was
	 * arguably acceptable under a prior version of the bindings).
	 * Let's make those old Chromebooks work by detecting that
	 * we're not a child of "reserved-memory" and mimicking the
	 * expected behavior.
	 */
	parent_node = of_get_parent(of_node);
	अगर (!of_node_name_eq(parent_node, "reserved-memory") &&
	    !pdata->console_size && !pdata->ftrace_size &&
	    !pdata->pmsg_size && !pdata->ecc_info.ecc_size) अणु
		pdata->console_size = pdata->record_size;
		pdata->pmsg_size = pdata->record_size;
	पूर्ण
	of_node_put(parent_node);

	वापस 0;
पूर्ण

अटल पूर्णांक ramoops_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ramoops_platक्रमm_data *pdata = dev->platक्रमm_data;
	काष्ठा ramoops_platक्रमm_data pdata_local;
	काष्ठा ramoops_context *cxt = &oops_cxt;
	माप_प्रकार dump_mem_sz;
	phys_addr_t paddr;
	पूर्णांक err = -EINVAL;

	/*
	 * Only a single ramoops area allowed at a समय, so fail extra
	 * probes.
	 */
	अगर (cxt->max_dump_cnt) अणु
		pr_err("already initialized\n");
		जाओ fail_out;
	पूर्ण

	अगर (dev_of_node(dev) && !pdata) अणु
		pdata = &pdata_local;
		स_रखो(pdata, 0, माप(*pdata));

		err = ramoops_parse_dt(pdev, pdata);
		अगर (err < 0)
			जाओ fail_out;
	पूर्ण

	/* Make sure we didn't get bogus platक्रमm data poपूर्णांकer. */
	अगर (!pdata) अणु
		pr_err("NULL platform data\n");
		जाओ fail_out;
	पूर्ण

	अगर (!pdata->mem_size || (!pdata->record_size && !pdata->console_size &&
			!pdata->ftrace_size && !pdata->pmsg_size)) अणु
		pr_err("The memory size and the record/console size must be "
			"non-zero\n");
		जाओ fail_out;
	पूर्ण

	अगर (pdata->record_size && !is_घातer_of_2(pdata->record_size))
		pdata->record_size = roundकरोwn_घात_of_two(pdata->record_size);
	अगर (pdata->console_size && !is_घातer_of_2(pdata->console_size))
		pdata->console_size = roundकरोwn_घात_of_two(pdata->console_size);
	अगर (pdata->ftrace_size && !is_घातer_of_2(pdata->ftrace_size))
		pdata->ftrace_size = roundकरोwn_घात_of_two(pdata->ftrace_size);
	अगर (pdata->pmsg_size && !is_घातer_of_2(pdata->pmsg_size))
		pdata->pmsg_size = roundकरोwn_घात_of_two(pdata->pmsg_size);

	cxt->size = pdata->mem_size;
	cxt->phys_addr = pdata->mem_address;
	cxt->memtype = pdata->mem_type;
	cxt->record_size = pdata->record_size;
	cxt->console_size = pdata->console_size;
	cxt->ftrace_size = pdata->ftrace_size;
	cxt->pmsg_size = pdata->pmsg_size;
	cxt->flags = pdata->flags;
	cxt->ecc_info = pdata->ecc_info;

	paddr = cxt->phys_addr;

	dump_mem_sz = cxt->size - cxt->console_size - cxt->ftrace_size
			- cxt->pmsg_size;
	err = ramoops_init_przs("dmesg", dev, cxt, &cxt->dprzs, &paddr,
				dump_mem_sz, cxt->record_size,
				&cxt->max_dump_cnt, 0, 0);
	अगर (err)
		जाओ fail_out;

	err = ramoops_init_prz("console", dev, cxt, &cxt->cprz, &paddr,
			       cxt->console_size, 0);
	अगर (err)
		जाओ fail_init_cprz;

	cxt->max_ftrace_cnt = (cxt->flags & RAMOOPS_FLAG_FTRACE_PER_CPU)
				? nr_cpu_ids
				: 1;
	err = ramoops_init_przs("ftrace", dev, cxt, &cxt->fprzs, &paddr,
				cxt->ftrace_size, -1,
				&cxt->max_ftrace_cnt, LINUX_VERSION_CODE,
				(cxt->flags & RAMOOPS_FLAG_FTRACE_PER_CPU)
					? PRZ_FLAG_NO_LOCK : 0);
	अगर (err)
		जाओ fail_init_fprz;

	err = ramoops_init_prz("pmsg", dev, cxt, &cxt->mprz, &paddr,
				cxt->pmsg_size, 0);
	अगर (err)
		जाओ fail_init_mprz;

	cxt->pstore.data = cxt;
	/*
	 * Prepare frontend flags based on which areas are initialized.
	 * For ramoops_init_przs() हालs, the "max count" variable tells
	 * अगर there are regions present. For ramoops_init_prz() हालs,
	 * the single region size is how to check.
	 */
	cxt->pstore.flags = 0;
	अगर (cxt->max_dump_cnt) अणु
		cxt->pstore.flags |= PSTORE_FLAGS_DMESG;
		cxt->pstore.max_reason = pdata->max_reason;
	पूर्ण
	अगर (cxt->console_size)
		cxt->pstore.flags |= PSTORE_FLAGS_CONSOLE;
	अगर (cxt->max_ftrace_cnt)
		cxt->pstore.flags |= PSTORE_FLAGS_FTRACE;
	अगर (cxt->pmsg_size)
		cxt->pstore.flags |= PSTORE_FLAGS_PMSG;

	/*
	 * Since bufsize is only used क्रम dmesg crash dumps, it
	 * must match the size of the dprz record (after PRZ header
	 * and ECC bytes have been accounted क्रम).
	 */
	अगर (cxt->pstore.flags & PSTORE_FLAGS_DMESG) अणु
		cxt->pstore.bufsize = cxt->dprzs[0]->buffer_size;
		cxt->pstore.buf = kzalloc(cxt->pstore.bufsize, GFP_KERNEL);
		अगर (!cxt->pstore.buf) अणु
			pr_err("cannot allocate pstore crash dump buffer\n");
			err = -ENOMEM;
			जाओ fail_clear;
		पूर्ण
	पूर्ण

	err = pstore_रेजिस्टर(&cxt->pstore);
	अगर (err) अणु
		pr_err("registering with pstore failed\n");
		जाओ fail_buf;
	पूर्ण

	/*
	 * Update the module parameter variables as well so they are visible
	 * through /sys/module/ramoops/parameters/
	 */
	mem_size = pdata->mem_size;
	mem_address = pdata->mem_address;
	record_size = pdata->record_size;
	ramoops_max_reason = pdata->max_reason;
	ramoops_console_size = pdata->console_size;
	ramoops_pmsg_size = pdata->pmsg_size;
	ramoops_ftrace_size = pdata->ftrace_size;

	pr_info("using 0x%lx@0x%llx, ecc: %d\n",
		cxt->size, (अचिन्हित दीर्घ दीर्घ)cxt->phys_addr,
		cxt->ecc_info.ecc_size);

	वापस 0;

fail_buf:
	kमुक्त(cxt->pstore.buf);
fail_clear:
	cxt->pstore.bufsize = 0;
	persistent_ram_मुक्त(cxt->mprz);
fail_init_mprz:
fail_init_fprz:
	persistent_ram_मुक्त(cxt->cprz);
fail_init_cprz:
	ramoops_मुक्त_przs(cxt);
fail_out:
	वापस err;
पूर्ण

अटल पूर्णांक ramoops_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ramoops_context *cxt = &oops_cxt;

	pstore_unरेजिस्टर(&cxt->pstore);

	kमुक्त(cxt->pstore.buf);
	cxt->pstore.bufsize = 0;

	persistent_ram_मुक्त(cxt->mprz);
	persistent_ram_मुक्त(cxt->cprz);
	ramoops_मुक्त_przs(cxt);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id dt_match[] = अणु
	अणु .compatible = "ramoops" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver ramoops_driver = अणु
	.probe		= ramoops_probe,
	.हटाओ		= ramoops_हटाओ,
	.driver		= अणु
		.name		= "ramoops",
		.of_match_table	= dt_match,
	पूर्ण,
पूर्ण;

अटल अंतरभूत व्योम ramoops_unरेजिस्टर_dummy(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(dummy);
	dummy = शून्य;
पूर्ण

अटल व्योम __init ramoops_रेजिस्टर_dummy(व्योम)
अणु
	काष्ठा ramoops_platक्रमm_data pdata;

	/*
	 * Prepare a dummy platक्रमm data काष्ठाure to carry the module
	 * parameters. If mem_size isn't set, then there are no module
	 * parameters, and we can skip this.
	 */
	अगर (!mem_size)
		वापस;

	pr_info("using module parameters\n");

	स_रखो(&pdata, 0, माप(pdata));
	pdata.mem_size = mem_size;
	pdata.mem_address = mem_address;
	pdata.mem_type = mem_type;
	pdata.record_size = record_size;
	pdata.console_size = ramoops_console_size;
	pdata.ftrace_size = ramoops_ftrace_size;
	pdata.pmsg_size = ramoops_pmsg_size;
	/* If "max_reason" is set, its value has priority over "dump_oops". */
	अगर (ramoops_max_reason >= 0)
		pdata.max_reason = ramoops_max_reason;
	/* Otherwise, अगर "dump_oops" is set, parse it पूर्णांकo "max_reason". */
	अन्यथा अगर (ramoops_dump_oops != -1)
		pdata.max_reason = ramoops_dump_oops ? KMSG_DUMP_OOPS
						     : KMSG_DUMP_PANIC;
	/* And अगर neither are explicitly set, use the शेष. */
	अन्यथा
		pdata.max_reason = KMSG_DUMP_OOPS;
	pdata.flags = RAMOOPS_FLAG_FTRACE_PER_CPU;

	/*
	 * For backwards compatibility ramoops.ecc=1 means 16 bytes ECC
	 * (using 1 byte क्रम ECC isn't much of use anyway).
	 */
	pdata.ecc_info.ecc_size = ramoops_ecc == 1 ? 16 : ramoops_ecc;

	dummy = platक्रमm_device_रेजिस्टर_data(शून्य, "ramoops", -1,
			&pdata, माप(pdata));
	अगर (IS_ERR(dummy)) अणु
		pr_info("could not create platform device: %ld\n",
			PTR_ERR(dummy));
		dummy = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक __init ramoops_init(व्योम)
अणु
	पूर्णांक ret;

	ramoops_रेजिस्टर_dummy();
	ret = platक्रमm_driver_रेजिस्टर(&ramoops_driver);
	अगर (ret != 0)
		ramoops_unरेजिस्टर_dummy();

	वापस ret;
पूर्ण
postcore_initcall(ramoops_init);

अटल व्योम __निकास ramoops_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ramoops_driver);
	ramoops_unरेजिस्टर_dummy();
पूर्ण
module_निकास(ramoops_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Marco Stornelli <marco.stornelli@gmail.com>");
MODULE_DESCRIPTION("RAM Oops/Panic logger/driver");

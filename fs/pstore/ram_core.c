<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Google, Inc.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/memblock.h>
#समावेश <linux/pstore_ram.h>
#समावेश <linux/rslib.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <यंत्र/page.h>

/**
 * काष्ठा persistent_ram_buffer - persistent circular RAM buffer
 *
 * @sig:
 *	signature to indicate header (PERSISTENT_RAM_SIG xor PRZ-type value)
 * @start:
 *	offset पूर्णांकo @data where the beginning of the stored bytes begin
 * @size:
 *	number of valid bytes stored in @data
 */
काष्ठा persistent_ram_buffer अणु
	uपूर्णांक32_t    sig;
	atomic_t    start;
	atomic_t    size;
	uपूर्णांक8_t     data[];
पूर्ण;

#घोषणा PERSISTENT_RAM_SIG (0x43474244) /* DBGC */

अटल अंतरभूत माप_प्रकार buffer_size(काष्ठा persistent_ram_zone *prz)
अणु
	वापस atomic_पढ़ो(&prz->buffer->size);
पूर्ण

अटल अंतरभूत माप_प्रकार buffer_start(काष्ठा persistent_ram_zone *prz)
अणु
	वापस atomic_पढ़ो(&prz->buffer->start);
पूर्ण

/* increase and wrap the start poपूर्णांकer, वापसing the old value */
अटल माप_प्रकार buffer_start_add(काष्ठा persistent_ram_zone *prz, माप_प्रकार a)
अणु
	पूर्णांक old;
	पूर्णांक new;
	अचिन्हित दीर्घ flags = 0;

	अगर (!(prz->flags & PRZ_FLAG_NO_LOCK))
		raw_spin_lock_irqsave(&prz->buffer_lock, flags);

	old = atomic_पढ़ो(&prz->buffer->start);
	new = old + a;
	जबतक (unlikely(new >= prz->buffer_size))
		new -= prz->buffer_size;
	atomic_set(&prz->buffer->start, new);

	अगर (!(prz->flags & PRZ_FLAG_NO_LOCK))
		raw_spin_unlock_irqrestore(&prz->buffer_lock, flags);

	वापस old;
पूर्ण

/* increase the size counter until it hits the max size */
अटल व्योम buffer_size_add(काष्ठा persistent_ram_zone *prz, माप_प्रकार a)
अणु
	माप_प्रकार old;
	माप_प्रकार new;
	अचिन्हित दीर्घ flags = 0;

	अगर (!(prz->flags & PRZ_FLAG_NO_LOCK))
		raw_spin_lock_irqsave(&prz->buffer_lock, flags);

	old = atomic_पढ़ो(&prz->buffer->size);
	अगर (old == prz->buffer_size)
		जाओ निकास;

	new = old + a;
	अगर (new > prz->buffer_size)
		new = prz->buffer_size;
	atomic_set(&prz->buffer->size, new);

निकास:
	अगर (!(prz->flags & PRZ_FLAG_NO_LOCK))
		raw_spin_unlock_irqrestore(&prz->buffer_lock, flags);
पूर्ण

अटल व्योम notrace persistent_ram_encode_rs8(काष्ठा persistent_ram_zone *prz,
	uपूर्णांक8_t *data, माप_प्रकार len, uपूर्णांक8_t *ecc)
अणु
	पूर्णांक i;

	/* Initialize the parity buffer */
	स_रखो(prz->ecc_info.par, 0,
	       prz->ecc_info.ecc_size * माप(prz->ecc_info.par[0]));
	encode_rs8(prz->rs_decoder, data, len, prz->ecc_info.par, 0);
	क्रम (i = 0; i < prz->ecc_info.ecc_size; i++)
		ecc[i] = prz->ecc_info.par[i];
पूर्ण

अटल पूर्णांक persistent_ram_decode_rs8(काष्ठा persistent_ram_zone *prz,
	व्योम *data, माप_प्रकार len, uपूर्णांक8_t *ecc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < prz->ecc_info.ecc_size; i++)
		prz->ecc_info.par[i] = ecc[i];
	वापस decode_rs8(prz->rs_decoder, data, prz->ecc_info.par, len,
				शून्य, 0, शून्य, 0, शून्य);
पूर्ण

अटल व्योम notrace persistent_ram_update_ecc(काष्ठा persistent_ram_zone *prz,
	अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक count)
अणु
	काष्ठा persistent_ram_buffer *buffer = prz->buffer;
	uपूर्णांक8_t *buffer_end = buffer->data + prz->buffer_size;
	uपूर्णांक8_t *block;
	uपूर्णांक8_t *par;
	पूर्णांक ecc_block_size = prz->ecc_info.block_size;
	पूर्णांक ecc_size = prz->ecc_info.ecc_size;
	पूर्णांक size = ecc_block_size;

	अगर (!ecc_size)
		वापस;

	block = buffer->data + (start & ~(ecc_block_size - 1));
	par = prz->par_buffer + (start / ecc_block_size) * ecc_size;

	करो अणु
		अगर (block + ecc_block_size > buffer_end)
			size = buffer_end - block;
		persistent_ram_encode_rs8(prz, block, size, par);
		block += ecc_block_size;
		par += ecc_size;
	पूर्ण जबतक (block < buffer->data + start + count);
पूर्ण

अटल व्योम persistent_ram_update_header_ecc(काष्ठा persistent_ram_zone *prz)
अणु
	काष्ठा persistent_ram_buffer *buffer = prz->buffer;

	अगर (!prz->ecc_info.ecc_size)
		वापस;

	persistent_ram_encode_rs8(prz, (uपूर्णांक8_t *)buffer, माप(*buffer),
				  prz->par_header);
पूर्ण

अटल व्योम persistent_ram_ecc_old(काष्ठा persistent_ram_zone *prz)
अणु
	काष्ठा persistent_ram_buffer *buffer = prz->buffer;
	uपूर्णांक8_t *block;
	uपूर्णांक8_t *par;

	अगर (!prz->ecc_info.ecc_size)
		वापस;

	block = buffer->data;
	par = prz->par_buffer;
	जबतक (block < buffer->data + buffer_size(prz)) अणु
		पूर्णांक numerr;
		पूर्णांक size = prz->ecc_info.block_size;
		अगर (block + size > buffer->data + prz->buffer_size)
			size = buffer->data + prz->buffer_size - block;
		numerr = persistent_ram_decode_rs8(prz, block, size, par);
		अगर (numerr > 0) अणु
			pr_devel("error in block %p, %d\n", block, numerr);
			prz->corrected_bytes += numerr;
		पूर्ण अन्यथा अगर (numerr < 0) अणु
			pr_devel("uncorrectable error in block %p\n", block);
			prz->bad_blocks++;
		पूर्ण
		block += prz->ecc_info.block_size;
		par += prz->ecc_info.ecc_size;
	पूर्ण
पूर्ण

अटल पूर्णांक persistent_ram_init_ecc(काष्ठा persistent_ram_zone *prz,
				   काष्ठा persistent_ram_ecc_info *ecc_info)
अणु
	पूर्णांक numerr;
	काष्ठा persistent_ram_buffer *buffer = prz->buffer;
	पूर्णांक ecc_blocks;
	माप_प्रकार ecc_total;

	अगर (!ecc_info || !ecc_info->ecc_size)
		वापस 0;

	prz->ecc_info.block_size = ecc_info->block_size ?: 128;
	prz->ecc_info.ecc_size = ecc_info->ecc_size ?: 16;
	prz->ecc_info.symsize = ecc_info->symsize ?: 8;
	prz->ecc_info.poly = ecc_info->poly ?: 0x11d;

	ecc_blocks = DIV_ROUND_UP(prz->buffer_size - prz->ecc_info.ecc_size,
				  prz->ecc_info.block_size +
				  prz->ecc_info.ecc_size);
	ecc_total = (ecc_blocks + 1) * prz->ecc_info.ecc_size;
	अगर (ecc_total >= prz->buffer_size) अणु
		pr_err("%s: invalid ecc_size %u (total %zu, buffer size %zu)\n",
		       __func__, prz->ecc_info.ecc_size,
		       ecc_total, prz->buffer_size);
		वापस -EINVAL;
	पूर्ण

	prz->buffer_size -= ecc_total;
	prz->par_buffer = buffer->data + prz->buffer_size;
	prz->par_header = prz->par_buffer +
			  ecc_blocks * prz->ecc_info.ecc_size;

	/*
	 * first consecutive root is 0
	 * primitive element to generate roots = 1
	 */
	prz->rs_decoder = init_rs(prz->ecc_info.symsize, prz->ecc_info.poly,
				  0, 1, prz->ecc_info.ecc_size);
	अगर (prz->rs_decoder == शून्य) अणु
		pr_info("init_rs failed\n");
		वापस -EINVAL;
	पूर्ण

	/* allocate workspace instead of using stack VLA */
	prz->ecc_info.par = kदो_स्मृति_array(prz->ecc_info.ecc_size,
					  माप(*prz->ecc_info.par),
					  GFP_KERNEL);
	अगर (!prz->ecc_info.par) अणु
		pr_err("cannot allocate ECC parity workspace\n");
		वापस -ENOMEM;
	पूर्ण

	prz->corrected_bytes = 0;
	prz->bad_blocks = 0;

	numerr = persistent_ram_decode_rs8(prz, buffer, माप(*buffer),
					   prz->par_header);
	अगर (numerr > 0) अणु
		pr_info("error in header, %d\n", numerr);
		prz->corrected_bytes += numerr;
	पूर्ण अन्यथा अगर (numerr < 0) अणु
		pr_info_ratelimited("uncorrectable error in header\n");
		prz->bad_blocks++;
	पूर्ण

	वापस 0;
पूर्ण

sमाप_प्रकार persistent_ram_ecc_string(काष्ठा persistent_ram_zone *prz,
	अक्षर *str, माप_प्रकार len)
अणु
	sमाप_प्रकार ret;

	अगर (!prz->ecc_info.ecc_size)
		वापस 0;

	अगर (prz->corrected_bytes || prz->bad_blocks)
		ret = snम_लिखो(str, len, ""
			"\n%d Corrected bytes, %d unrecoverable blocks\n",
			prz->corrected_bytes, prz->bad_blocks);
	अन्यथा
		ret = snम_लिखो(str, len, "\nNo errors detected\n");

	वापस ret;
पूर्ण

अटल व्योम notrace persistent_ram_update(काष्ठा persistent_ram_zone *prz,
	स्थिर व्योम *s, अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक count)
अणु
	काष्ठा persistent_ram_buffer *buffer = prz->buffer;
	स_नकल_toio(buffer->data + start, s, count);
	persistent_ram_update_ecc(prz, start, count);
पूर्ण

अटल पूर्णांक notrace persistent_ram_update_user(काष्ठा persistent_ram_zone *prz,
	स्थिर व्योम __user *s, अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक count)
अणु
	काष्ठा persistent_ram_buffer *buffer = prz->buffer;
	पूर्णांक ret = unlikely(copy_from_user(buffer->data + start, s, count)) ?
		-EFAULT : 0;
	persistent_ram_update_ecc(prz, start, count);
	वापस ret;
पूर्ण

व्योम persistent_ram_save_old(काष्ठा persistent_ram_zone *prz)
अणु
	काष्ठा persistent_ram_buffer *buffer = prz->buffer;
	माप_प्रकार size = buffer_size(prz);
	माप_प्रकार start = buffer_start(prz);

	अगर (!size)
		वापस;

	अगर (!prz->old_log) अणु
		persistent_ram_ecc_old(prz);
		prz->old_log = kदो_स्मृति(size, GFP_KERNEL);
	पूर्ण
	अगर (!prz->old_log) अणु
		pr_err("failed to allocate buffer\n");
		वापस;
	पूर्ण

	prz->old_log_size = size;
	स_नकल_fromio(prz->old_log, &buffer->data[start], size - start);
	स_नकल_fromio(prz->old_log + size - start, &buffer->data[0], start);
पूर्ण

पूर्णांक notrace persistent_ram_ग_लिखो(काष्ठा persistent_ram_zone *prz,
	स्थिर व्योम *s, अचिन्हित पूर्णांक count)
अणु
	पूर्णांक rem;
	पूर्णांक c = count;
	माप_प्रकार start;

	अगर (unlikely(c > prz->buffer_size)) अणु
		s += c - prz->buffer_size;
		c = prz->buffer_size;
	पूर्ण

	buffer_size_add(prz, c);

	start = buffer_start_add(prz, c);

	rem = prz->buffer_size - start;
	अगर (unlikely(rem < c)) अणु
		persistent_ram_update(prz, s, start, rem);
		s += rem;
		c -= rem;
		start = 0;
	पूर्ण
	persistent_ram_update(prz, s, start, c);

	persistent_ram_update_header_ecc(prz);

	वापस count;
पूर्ण

पूर्णांक notrace persistent_ram_ग_लिखो_user(काष्ठा persistent_ram_zone *prz,
	स्थिर व्योम __user *s, अचिन्हित पूर्णांक count)
अणु
	पूर्णांक rem, ret = 0, c = count;
	माप_प्रकार start;

	अगर (unlikely(c > prz->buffer_size)) अणु
		s += c - prz->buffer_size;
		c = prz->buffer_size;
	पूर्ण

	buffer_size_add(prz, c);

	start = buffer_start_add(prz, c);

	rem = prz->buffer_size - start;
	अगर (unlikely(rem < c)) अणु
		ret = persistent_ram_update_user(prz, s, start, rem);
		s += rem;
		c -= rem;
		start = 0;
	पूर्ण
	अगर (likely(!ret))
		ret = persistent_ram_update_user(prz, s, start, c);

	persistent_ram_update_header_ecc(prz);

	वापस unlikely(ret) ? ret : count;
पूर्ण

माप_प्रकार persistent_ram_old_size(काष्ठा persistent_ram_zone *prz)
अणु
	वापस prz->old_log_size;
पूर्ण

व्योम *persistent_ram_old(काष्ठा persistent_ram_zone *prz)
अणु
	वापस prz->old_log;
पूर्ण

व्योम persistent_ram_मुक्त_old(काष्ठा persistent_ram_zone *prz)
अणु
	kमुक्त(prz->old_log);
	prz->old_log = शून्य;
	prz->old_log_size = 0;
पूर्ण

व्योम persistent_ram_zap(काष्ठा persistent_ram_zone *prz)
अणु
	atomic_set(&prz->buffer->start, 0);
	atomic_set(&prz->buffer->size, 0);
	persistent_ram_update_header_ecc(prz);
पूर्ण

#घोषणा MEM_TYPE_WCOMBINE	0
#घोषणा MEM_TYPE_NONCACHED	1
#घोषणा MEM_TYPE_NORMAL		2

अटल व्योम *persistent_ram_vmap(phys_addr_t start, माप_प्रकार size,
		अचिन्हित पूर्णांक memtype)
अणु
	काष्ठा page **pages;
	phys_addr_t page_start;
	अचिन्हित पूर्णांक page_count;
	pgprot_t prot;
	अचिन्हित पूर्णांक i;
	व्योम *vaddr;

	page_start = start - offset_in_page(start);
	page_count = DIV_ROUND_UP(size + offset_in_page(start), PAGE_SIZE);

	चयन (memtype) अणु
	हाल MEM_TYPE_NORMAL:
		prot = PAGE_KERNEL;
		अवरोध;
	हाल MEM_TYPE_NONCACHED:
		prot = pgprot_noncached(PAGE_KERNEL);
		अवरोध;
	हाल MEM_TYPE_WCOMBINE:
		prot = pgprot_ग_लिखोcombine(PAGE_KERNEL);
		अवरोध;
	शेष:
		pr_err("invalid mem_type=%d\n", memtype);
		वापस शून्य;
	पूर्ण

	pages = kदो_स्मृति_array(page_count, माप(काष्ठा page *), GFP_KERNEL);
	अगर (!pages) अणु
		pr_err("%s: Failed to allocate array for %u pages\n",
		       __func__, page_count);
		वापस शून्य;
	पूर्ण

	क्रम (i = 0; i < page_count; i++) अणु
		phys_addr_t addr = page_start + i * PAGE_SIZE;
		pages[i] = pfn_to_page(addr >> PAGE_SHIFT);
	पूर्ण
	vaddr = vmap(pages, page_count, VM_MAP, prot);
	kमुक्त(pages);

	/*
	 * Since vmap() uses page granularity, we must add the offset
	 * पूर्णांकo the page here, to get the byte granularity address
	 * पूर्णांकo the mapping to represent the actual "start" location.
	 */
	वापस vaddr + offset_in_page(start);
पूर्ण

अटल व्योम *persistent_ram_iomap(phys_addr_t start, माप_प्रकार size,
		अचिन्हित पूर्णांक memtype, अक्षर *label)
अणु
	व्योम *va;

	अगर (!request_mem_region(start, size, label ?: "ramoops")) अणु
		pr_err("request mem region (%s 0x%llx@0x%llx) failed\n",
			label ?: "ramoops",
			(अचिन्हित दीर्घ दीर्घ)size, (अचिन्हित दीर्घ दीर्घ)start);
		वापस शून्य;
	पूर्ण

	अगर (memtype)
		va = ioremap(start, size);
	अन्यथा
		va = ioremap_wc(start, size);

	/*
	 * Since request_mem_region() and ioremap() are byte-granularity
	 * there is no need handle anything special like we करो when the
	 * vmap() हाल in persistent_ram_vmap() above.
	 */
	वापस va;
पूर्ण

अटल पूर्णांक persistent_ram_buffer_map(phys_addr_t start, phys_addr_t size,
		काष्ठा persistent_ram_zone *prz, पूर्णांक memtype)
अणु
	prz->paddr = start;
	prz->size = size;

	अगर (pfn_valid(start >> PAGE_SHIFT))
		prz->vaddr = persistent_ram_vmap(start, size, memtype);
	अन्यथा
		prz->vaddr = persistent_ram_iomap(start, size, memtype,
						  prz->label);

	अगर (!prz->vaddr) अणु
		pr_err("%s: Failed to map 0x%llx pages at 0x%llx\n", __func__,
			(अचिन्हित दीर्घ दीर्घ)size, (अचिन्हित दीर्घ दीर्घ)start);
		वापस -ENOMEM;
	पूर्ण

	prz->buffer = prz->vaddr;
	prz->buffer_size = size - माप(काष्ठा persistent_ram_buffer);

	वापस 0;
पूर्ण

अटल पूर्णांक persistent_ram_post_init(काष्ठा persistent_ram_zone *prz, u32 sig,
				    काष्ठा persistent_ram_ecc_info *ecc_info)
अणु
	पूर्णांक ret;
	bool zap = !!(prz->flags & PRZ_FLAG_ZAP_OLD);

	ret = persistent_ram_init_ecc(prz, ecc_info);
	अगर (ret) अणु
		pr_warn("ECC failed %s\n", prz->label);
		वापस ret;
	पूर्ण

	sig ^= PERSISTENT_RAM_SIG;

	अगर (prz->buffer->sig == sig) अणु
		अगर (buffer_size(prz) == 0) अणु
			pr_debug("found existing empty buffer\n");
			वापस 0;
		पूर्ण

		अगर (buffer_size(prz) > prz->buffer_size ||
		    buffer_start(prz) > buffer_size(prz)) अणु
			pr_info("found existing invalid buffer, size %zu, start %zu\n",
				buffer_size(prz), buffer_start(prz));
			zap = true;
		पूर्ण अन्यथा अणु
			pr_debug("found existing buffer, size %zu, start %zu\n",
				 buffer_size(prz), buffer_start(prz));
			persistent_ram_save_old(prz);
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_debug("no valid data in buffer (sig = 0x%08x)\n",
			 prz->buffer->sig);
		prz->buffer->sig = sig;
		zap = true;
	पूर्ण

	/* Reset missing, invalid, or single-use memory area. */
	अगर (zap)
		persistent_ram_zap(prz);

	वापस 0;
पूर्ण

व्योम persistent_ram_मुक्त(काष्ठा persistent_ram_zone *prz)
अणु
	अगर (!prz)
		वापस;

	अगर (prz->vaddr) अणु
		अगर (pfn_valid(prz->paddr >> PAGE_SHIFT)) अणु
			/* We must vunmap() at page-granularity. */
			vunmap(prz->vaddr - offset_in_page(prz->paddr));
		पूर्ण अन्यथा अणु
			iounmap(prz->vaddr);
			release_mem_region(prz->paddr, prz->size);
		पूर्ण
		prz->vaddr = शून्य;
	पूर्ण
	अगर (prz->rs_decoder) अणु
		मुक्त_rs(prz->rs_decoder);
		prz->rs_decoder = शून्य;
	पूर्ण
	kमुक्त(prz->ecc_info.par);
	prz->ecc_info.par = शून्य;

	persistent_ram_मुक्त_old(prz);
	kमुक्त(prz->label);
	kमुक्त(prz);
पूर्ण

काष्ठा persistent_ram_zone *persistent_ram_new(phys_addr_t start, माप_प्रकार size,
			u32 sig, काष्ठा persistent_ram_ecc_info *ecc_info,
			अचिन्हित पूर्णांक memtype, u32 flags, अक्षर *label)
अणु
	काष्ठा persistent_ram_zone *prz;
	पूर्णांक ret = -ENOMEM;

	prz = kzalloc(माप(काष्ठा persistent_ram_zone), GFP_KERNEL);
	अगर (!prz) अणु
		pr_err("failed to allocate persistent ram zone\n");
		जाओ err;
	पूर्ण

	/* Initialize general buffer state. */
	raw_spin_lock_init(&prz->buffer_lock);
	prz->flags = flags;
	prz->label = kstrdup(label, GFP_KERNEL);

	ret = persistent_ram_buffer_map(start, size, prz, memtype);
	अगर (ret)
		जाओ err;

	ret = persistent_ram_post_init(prz, sig, ecc_info);
	अगर (ret)
		जाओ err;

	pr_debug("attached %s 0x%zx@0x%llx: %zu header, %zu data, %zu ecc (%d/%d)\n",
		prz->label, prz->size, (अचिन्हित दीर्घ दीर्घ)prz->paddr,
		माप(*prz->buffer), prz->buffer_size,
		prz->size - माप(*prz->buffer) - prz->buffer_size,
		prz->ecc_info.ecc_size, prz->ecc_info.block_size);

	वापस prz;
err:
	persistent_ram_मुक्त(prz);
	वापस ERR_PTR(ret);
पूर्ण

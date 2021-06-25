<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright IBM Corp. 2007,2012
 *
 * Author(s): Heiko Carstens <heiko.carstens@de.ibm.com>,
 *	      Peter Oberparleiter <peter.oberparleiter@de.ibm.com>
 */

#घोषणा KMSG_COMPONENT "sclp_cmd"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/completion.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/memory.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <यंत्र/ctl_reg.h>
#समावेश <यंत्र/chpid.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/sclp.h>
#समावेश <यंत्र/numa.h>
#समावेश <यंत्र/facility.h>

#समावेश "sclp.h"

अटल व्योम sclp_sync_callback(काष्ठा sclp_req *req, व्योम *data)
अणु
	काष्ठा completion *completion = data;

	complete(completion);
पूर्ण

पूर्णांक sclp_sync_request(sclp_cmdw_t cmd, व्योम *sccb)
अणु
	वापस sclp_sync_request_समयout(cmd, sccb, 0);
पूर्ण

पूर्णांक sclp_sync_request_समयout(sclp_cmdw_t cmd, व्योम *sccb, पूर्णांक समयout)
अणु
	काष्ठा completion completion;
	काष्ठा sclp_req *request;
	पूर्णांक rc;

	request = kzalloc(माप(*request), GFP_KERNEL);
	अगर (!request)
		वापस -ENOMEM;
	अगर (समयout)
		request->queue_समयout = समयout;
	request->command = cmd;
	request->sccb = sccb;
	request->status = SCLP_REQ_FILLED;
	request->callback = sclp_sync_callback;
	request->callback_data = &completion;
	init_completion(&completion);

	/* Perक्रमm sclp request. */
	rc = sclp_add_request(request);
	अगर (rc)
		जाओ out;
	रुको_क्रम_completion(&completion);

	/* Check response. */
	अगर (request->status != SCLP_REQ_DONE) अणु
		pr_warn("sync request failed (cmd=0x%08x, status=0x%02x)\n",
			cmd, request->status);
		rc = -EIO;
	पूर्ण
out:
	kमुक्त(request);
	वापस rc;
पूर्ण

/*
 * CPU configuration related functions.
 */

#घोषणा SCLP_CMDW_CONFIGURE_CPU		0x00110001
#घोषणा SCLP_CMDW_DECONFIGURE_CPU	0x00100001

पूर्णांक _sclp_get_core_info(काष्ठा sclp_core_info *info)
अणु
	पूर्णांक rc;
	पूर्णांक length = test_facility(140) ? EXT_SCCB_READ_CPU : PAGE_SIZE;
	काष्ठा पढ़ो_cpu_info_sccb *sccb;

	अगर (!SCLP_HAS_CPU_INFO)
		वापस -EOPNOTSUPP;

	sccb = (व्योम *)__get_मुक्त_pages(GFP_KERNEL | GFP_DMA | __GFP_ZERO, get_order(length));
	अगर (!sccb)
		वापस -ENOMEM;
	sccb->header.length = length;
	sccb->header.control_mask[2] = 0x80;
	rc = sclp_sync_request_समयout(SCLP_CMDW_READ_CPU_INFO, sccb,
				       SCLP_QUEUE_INTERVAL);
	अगर (rc)
		जाओ out;
	अगर (sccb->header.response_code != 0x0010) अणु
		pr_warn("readcpuinfo failed (response=0x%04x)\n",
			sccb->header.response_code);
		rc = -EIO;
		जाओ out;
	पूर्ण
	sclp_fill_core_info(info, sccb);
out:
	मुक्त_pages((अचिन्हित दीर्घ) sccb, get_order(length));
	वापस rc;
पूर्ण

काष्ठा cpu_configure_sccb अणु
	काष्ठा sccb_header header;
पूर्ण __attribute__((packed, aligned(8)));

अटल पूर्णांक करो_core_configure(sclp_cmdw_t cmd)
अणु
	काष्ठा cpu_configure_sccb *sccb;
	पूर्णांक rc;

	अगर (!SCLP_HAS_CPU_RECONFIG)
		वापस -EOPNOTSUPP;
	/*
	 * This is not going to cross a page boundary since we क्रमce
	 * kदो_स्मृति to have a minimum alignment of 8 bytes on s390.
	 */
	sccb = kzalloc(माप(*sccb), GFP_KERNEL | GFP_DMA);
	अगर (!sccb)
		वापस -ENOMEM;
	sccb->header.length = माप(*sccb);
	rc = sclp_sync_request_समयout(cmd, sccb, SCLP_QUEUE_INTERVAL);
	अगर (rc)
		जाओ out;
	चयन (sccb->header.response_code) अणु
	हाल 0x0020:
	हाल 0x0120:
		अवरोध;
	शेष:
		pr_warn("configure cpu failed (cmd=0x%08x, response=0x%04x)\n",
			cmd, sccb->header.response_code);
		rc = -EIO;
		अवरोध;
	पूर्ण
out:
	kमुक्त(sccb);
	वापस rc;
पूर्ण

पूर्णांक sclp_core_configure(u8 core)
अणु
	वापस करो_core_configure(SCLP_CMDW_CONFIGURE_CPU | core << 8);
पूर्ण

पूर्णांक sclp_core_deconfigure(u8 core)
अणु
	वापस करो_core_configure(SCLP_CMDW_DECONFIGURE_CPU | core << 8);
पूर्ण

#अगर_घोषित CONFIG_MEMORY_HOTPLUG

अटल DEFINE_MUTEX(sclp_mem_mutex);
अटल LIST_HEAD(sclp_mem_list);
अटल u8 sclp_max_storage_id;
अटल DECLARE_BITMAP(sclp_storage_ids, 256);
अटल पूर्णांक sclp_mem_state_changed;

काष्ठा memory_increment अणु
	काष्ठा list_head list;
	u16 rn;
	पूर्णांक standby;
पूर्ण;

काष्ठा assign_storage_sccb अणु
	काष्ठा sccb_header header;
	u16 rn;
पूर्ण __packed;

पूर्णांक arch_get_memory_phys_device(अचिन्हित दीर्घ start_pfn)
अणु
	अगर (!sclp.rzm)
		वापस 0;
	वापस PFN_PHYS(start_pfn) >> ilog2(sclp.rzm);
पूर्ण

अटल अचिन्हित दीर्घ दीर्घ rn2addr(u16 rn)
अणु
	वापस (अचिन्हित दीर्घ दीर्घ) (rn - 1) * sclp.rzm;
पूर्ण

अटल पूर्णांक करो_assign_storage(sclp_cmdw_t cmd, u16 rn)
अणु
	काष्ठा assign_storage_sccb *sccb;
	पूर्णांक rc;

	sccb = (व्योम *) get_zeroed_page(GFP_KERNEL | GFP_DMA);
	अगर (!sccb)
		वापस -ENOMEM;
	sccb->header.length = PAGE_SIZE;
	sccb->rn = rn;
	rc = sclp_sync_request_समयout(cmd, sccb, SCLP_QUEUE_INTERVAL);
	अगर (rc)
		जाओ out;
	चयन (sccb->header.response_code) अणु
	हाल 0x0020:
	हाल 0x0120:
		अवरोध;
	शेष:
		pr_warn("assign storage failed (cmd=0x%08x, response=0x%04x, rn=0x%04x)\n",
			cmd, sccb->header.response_code, rn);
		rc = -EIO;
		अवरोध;
	पूर्ण
out:
	मुक्त_page((अचिन्हित दीर्घ) sccb);
	वापस rc;
पूर्ण

अटल पूर्णांक sclp_assign_storage(u16 rn)
अणु
	अचिन्हित दीर्घ दीर्घ start;
	पूर्णांक rc;

	rc = करो_assign_storage(0x000d0001, rn);
	अगर (rc)
		वापस rc;
	start = rn2addr(rn);
	storage_key_init_range(start, start + sclp.rzm);
	वापस 0;
पूर्ण

अटल पूर्णांक sclp_unassign_storage(u16 rn)
अणु
	वापस करो_assign_storage(0x000c0001, rn);
पूर्ण

काष्ठा attach_storage_sccb अणु
	काष्ठा sccb_header header;
	u16 :16;
	u16 asचिन्हित;
	u32 :32;
	u32 entries[0];
पूर्ण __packed;

अटल पूर्णांक sclp_attach_storage(u8 id)
अणु
	काष्ठा attach_storage_sccb *sccb;
	पूर्णांक rc;
	पूर्णांक i;

	sccb = (व्योम *) get_zeroed_page(GFP_KERNEL | GFP_DMA);
	अगर (!sccb)
		वापस -ENOMEM;
	sccb->header.length = PAGE_SIZE;
	sccb->header.function_code = 0x40;
	rc = sclp_sync_request_समयout(0x00080001 | id << 8, sccb,
				       SCLP_QUEUE_INTERVAL);
	अगर (rc)
		जाओ out;
	चयन (sccb->header.response_code) अणु
	हाल 0x0020:
		set_bit(id, sclp_storage_ids);
		क्रम (i = 0; i < sccb->asचिन्हित; i++) अणु
			अगर (sccb->entries[i])
				sclp_unassign_storage(sccb->entries[i] >> 16);
		पूर्ण
		अवरोध;
	शेष:
		rc = -EIO;
		अवरोध;
	पूर्ण
out:
	मुक्त_page((अचिन्हित दीर्घ) sccb);
	वापस rc;
पूर्ण

अटल पूर्णांक sclp_mem_change_state(अचिन्हित दीर्घ start, अचिन्हित दीर्घ size,
				 पूर्णांक online)
अणु
	काष्ठा memory_increment *incr;
	अचिन्हित दीर्घ दीर्घ istart;
	पूर्णांक rc = 0;

	list_क्रम_each_entry(incr, &sclp_mem_list, list) अणु
		istart = rn2addr(incr->rn);
		अगर (start + size - 1 < istart)
			अवरोध;
		अगर (start > istart + sclp.rzm - 1)
			जारी;
		अगर (online)
			rc |= sclp_assign_storage(incr->rn);
		अन्यथा
			sclp_unassign_storage(incr->rn);
		अगर (rc == 0)
			incr->standby = online ? 0 : 1;
	पूर्ण
	वापस rc ? -EIO : 0;
पूर्ण

अटल bool contains_standby_increment(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	काष्ठा memory_increment *incr;
	अचिन्हित दीर्घ istart;

	list_क्रम_each_entry(incr, &sclp_mem_list, list) अणु
		istart = rn2addr(incr->rn);
		अगर (end - 1 < istart)
			जारी;
		अगर (start > istart + sclp.rzm - 1)
			जारी;
		अगर (incr->standby)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक sclp_mem_notअगरier(काष्ठा notअगरier_block *nb,
			     अचिन्हित दीर्घ action, व्योम *data)
अणु
	अचिन्हित दीर्घ start, size;
	काष्ठा memory_notअगरy *arg;
	अचिन्हित अक्षर id;
	पूर्णांक rc = 0;

	arg = data;
	start = arg->start_pfn << PAGE_SHIFT;
	size = arg->nr_pages << PAGE_SHIFT;
	mutex_lock(&sclp_mem_mutex);
	क्रम_each_clear_bit(id, sclp_storage_ids, sclp_max_storage_id + 1)
		sclp_attach_storage(id);
	चयन (action) अणु
	हाल MEM_GOING_OFFLINE:
		/*
		 * We करो not allow to set memory blocks offline that contain
		 * standby memory. This is करोne to simplअगरy the "memory online"
		 * हाल.
		 */
		अगर (contains_standby_increment(start, start + size))
			rc = -EPERM;
		अवरोध;
	हाल MEM_ONLINE:
	हाल MEM_CANCEL_OFFLINE:
		अवरोध;
	हाल MEM_GOING_ONLINE:
		rc = sclp_mem_change_state(start, size, 1);
		अवरोध;
	हाल MEM_CANCEL_ONLINE:
		sclp_mem_change_state(start, size, 0);
		अवरोध;
	हाल MEM_OFFLINE:
		sclp_mem_change_state(start, size, 0);
		अवरोध;
	शेष:
		rc = -EINVAL;
		अवरोध;
	पूर्ण
	अगर (!rc)
		sclp_mem_state_changed = 1;
	mutex_unlock(&sclp_mem_mutex);
	वापस rc ? NOTIFY_BAD : NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block sclp_mem_nb = अणु
	.notअगरier_call = sclp_mem_notअगरier,
पूर्ण;

अटल व्योम __init align_to_block_size(अचिन्हित दीर्घ दीर्घ *start,
				       अचिन्हित दीर्घ दीर्घ *size,
				       अचिन्हित दीर्घ दीर्घ alignment)
अणु
	अचिन्हित दीर्घ दीर्घ start_align, size_align;

	start_align = roundup(*start, alignment);
	size_align = roundकरोwn(*start + *size, alignment) - start_align;

	pr_info("Standby memory at 0x%llx (%lluM of %lluM usable)\n",
		*start, size_align >> 20, *size >> 20);
	*start = start_align;
	*size = size_align;
पूर्ण

अटल व्योम __init add_memory_merged(u16 rn)
अणु
	अचिन्हित दीर्घ दीर्घ start, size, addr, block_size;
	अटल u16 first_rn, num;

	अगर (rn && first_rn && (first_rn + num == rn)) अणु
		num++;
		वापस;
	पूर्ण
	अगर (!first_rn)
		जाओ skip_add;
	start = rn2addr(first_rn);
	size = (अचिन्हित दीर्घ दीर्घ) num * sclp.rzm;
	अगर (start >= VMEM_MAX_PHYS)
		जाओ skip_add;
	अगर (start + size > VMEM_MAX_PHYS)
		size = VMEM_MAX_PHYS - start;
	अगर (start >= ident_map_size)
		जाओ skip_add;
	अगर (start + size > ident_map_size)
		size = ident_map_size - start;
	block_size = memory_block_size_bytes();
	align_to_block_size(&start, &size, block_size);
	अगर (!size)
		जाओ skip_add;
	क्रम (addr = start; addr < start + size; addr += block_size)
		add_memory(0, addr, block_size, MHP_NONE);
skip_add:
	first_rn = rn;
	num = 1;
पूर्ण

अटल व्योम __init sclp_add_standby_memory(व्योम)
अणु
	काष्ठा memory_increment *incr;

	list_क्रम_each_entry(incr, &sclp_mem_list, list)
		अगर (incr->standby)
			add_memory_merged(incr->rn);
	add_memory_merged(0);
पूर्ण

अटल व्योम __init insert_increment(u16 rn, पूर्णांक standby, पूर्णांक asचिन्हित)
अणु
	काष्ठा memory_increment *incr, *new_incr;
	काष्ठा list_head *prev;
	u16 last_rn;

	new_incr = kzalloc(माप(*new_incr), GFP_KERNEL);
	अगर (!new_incr)
		वापस;
	new_incr->rn = rn;
	new_incr->standby = standby;
	last_rn = 0;
	prev = &sclp_mem_list;
	list_क्रम_each_entry(incr, &sclp_mem_list, list) अणु
		अगर (asचिन्हित && incr->rn > rn)
			अवरोध;
		अगर (!asचिन्हित && incr->rn - last_rn > 1)
			अवरोध;
		last_rn = incr->rn;
		prev = &incr->list;
	पूर्ण
	अगर (!asचिन्हित)
		new_incr->rn = last_rn + 1;
	अगर (new_incr->rn > sclp.rnmax) अणु
		kमुक्त(new_incr);
		वापस;
	पूर्ण
	list_add(&new_incr->list, prev);
पूर्ण

अटल पूर्णांक sclp_mem_मुक्तze(काष्ठा device *dev)
अणु
	अगर (!sclp_mem_state_changed)
		वापस 0;
	pr_err("Memory hotplug state changed, suspend refused.\n");
	वापस -EPERM;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops sclp_mem_pm_ops = अणु
	.मुक्तze		= sclp_mem_मुक्तze,
पूर्ण;

अटल काष्ठा platक्रमm_driver sclp_mem_pdrv = अणु
	.driver = अणु
		.name	= "sclp_mem",
		.pm	= &sclp_mem_pm_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init sclp_detect_standby_memory(व्योम)
अणु
	काष्ठा platक्रमm_device *sclp_pdev;
	काष्ठा पढ़ो_storage_sccb *sccb;
	पूर्णांक i, id, asचिन्हित, rc;

	अगर (OLDMEM_BASE) /* No standby memory in kdump mode */
		वापस 0;
	अगर ((sclp.facilities & 0xe00000000000ULL) != 0xe00000000000ULL)
		वापस 0;
	rc = -ENOMEM;
	sccb = (व्योम *) __get_मुक्त_page(GFP_KERNEL | GFP_DMA);
	अगर (!sccb)
		जाओ out;
	asचिन्हित = 0;
	क्रम (id = 0; id <= sclp_max_storage_id; id++) अणु
		स_रखो(sccb, 0, PAGE_SIZE);
		sccb->header.length = PAGE_SIZE;
		rc = sclp_sync_request(SCLP_CMDW_READ_STORAGE_INFO | id << 8, sccb);
		अगर (rc)
			जाओ out;
		चयन (sccb->header.response_code) अणु
		हाल 0x0010:
			set_bit(id, sclp_storage_ids);
			क्रम (i = 0; i < sccb->asचिन्हित; i++) अणु
				अगर (!sccb->entries[i])
					जारी;
				asचिन्हित++;
				insert_increment(sccb->entries[i] >> 16, 0, 1);
			पूर्ण
			अवरोध;
		हाल 0x0310:
			अवरोध;
		हाल 0x0410:
			क्रम (i = 0; i < sccb->asचिन्हित; i++) अणु
				अगर (!sccb->entries[i])
					जारी;
				asचिन्हित++;
				insert_increment(sccb->entries[i] >> 16, 1, 1);
			पूर्ण
			अवरोध;
		शेष:
			rc = -EIO;
			अवरोध;
		पूर्ण
		अगर (!rc)
			sclp_max_storage_id = sccb->max_id;
	पूर्ण
	अगर (rc || list_empty(&sclp_mem_list))
		जाओ out;
	क्रम (i = 1; i <= sclp.rnmax - asचिन्हित; i++)
		insert_increment(0, 1, 0);
	rc = रेजिस्टर_memory_notअगरier(&sclp_mem_nb);
	अगर (rc)
		जाओ out;
	rc = platक्रमm_driver_रेजिस्टर(&sclp_mem_pdrv);
	अगर (rc)
		जाओ out;
	sclp_pdev = platक्रमm_device_रेजिस्टर_simple("sclp_mem", -1, शून्य, 0);
	rc = PTR_ERR_OR_ZERO(sclp_pdev);
	अगर (rc)
		जाओ out_driver;
	sclp_add_standby_memory();
	जाओ out;
out_driver:
	platक्रमm_driver_unरेजिस्टर(&sclp_mem_pdrv);
out:
	मुक्त_page((अचिन्हित दीर्घ) sccb);
	वापस rc;
पूर्ण
__initcall(sclp_detect_standby_memory);

#पूर्ण_अगर /* CONFIG_MEMORY_HOTPLUG */

/*
 * Channel path configuration related functions.
 */

#घोषणा SCLP_CMDW_CONFIGURE_CHPATH		0x000f0001
#घोषणा SCLP_CMDW_DECONFIGURE_CHPATH		0x000e0001
#घोषणा SCLP_CMDW_READ_CHPATH_INFORMATION	0x00030001

काष्ठा chp_cfg_sccb अणु
	काष्ठा sccb_header header;
	u8 ccm;
	u8 reserved[6];
	u8 cssid;
पूर्ण __attribute__((packed));

अटल पूर्णांक करो_chp_configure(sclp_cmdw_t cmd)
अणु
	काष्ठा chp_cfg_sccb *sccb;
	पूर्णांक rc;

	अगर (!SCLP_HAS_CHP_RECONFIG)
		वापस -EOPNOTSUPP;
	/* Prepare sccb. */
	sccb = (काष्ठा chp_cfg_sccb *) get_zeroed_page(GFP_KERNEL | GFP_DMA);
	अगर (!sccb)
		वापस -ENOMEM;
	sccb->header.length = माप(*sccb);
	rc = sclp_sync_request(cmd, sccb);
	अगर (rc)
		जाओ out;
	चयन (sccb->header.response_code) अणु
	हाल 0x0020:
	हाल 0x0120:
	हाल 0x0440:
	हाल 0x0450:
		अवरोध;
	शेष:
		pr_warn("configure channel-path failed (cmd=0x%08x, response=0x%04x)\n",
			cmd, sccb->header.response_code);
		rc = -EIO;
		अवरोध;
	पूर्ण
out:
	मुक्त_page((अचिन्हित दीर्घ) sccb);
	वापस rc;
पूर्ण

/**
 * sclp_chp_configure - perक्रमm configure channel-path sclp command
 * @chpid: channel-path ID
 *
 * Perक्रमm configure channel-path command sclp command क्रम specअगरied chpid.
 * Return 0 after command successfully finished, non-zero otherwise.
 */
पूर्णांक sclp_chp_configure(काष्ठा chp_id chpid)
अणु
	वापस करो_chp_configure(SCLP_CMDW_CONFIGURE_CHPATH | chpid.id << 8);
पूर्ण

/**
 * sclp_chp_deconfigure - perक्रमm deconfigure channel-path sclp command
 * @chpid: channel-path ID
 *
 * Perक्रमm deconfigure channel-path command sclp command क्रम specअगरied chpid
 * and रुको क्रम completion. On success वापस 0. Return non-zero otherwise.
 */
पूर्णांक sclp_chp_deconfigure(काष्ठा chp_id chpid)
अणु
	वापस करो_chp_configure(SCLP_CMDW_DECONFIGURE_CHPATH | chpid.id << 8);
पूर्ण

काष्ठा chp_info_sccb अणु
	काष्ठा sccb_header header;
	u8 recognized[SCLP_CHP_INFO_MASK_SIZE];
	u8 standby[SCLP_CHP_INFO_MASK_SIZE];
	u8 configured[SCLP_CHP_INFO_MASK_SIZE];
	u8 ccm;
	u8 reserved[6];
	u8 cssid;
पूर्ण __attribute__((packed));

/**
 * sclp_chp_पढ़ो_info - perक्रमm पढ़ो channel-path inक्रमmation sclp command
 * @info: resulting channel-path inक्रमmation data
 *
 * Perक्रमm पढ़ो channel-path inक्रमmation sclp command and रुको क्रम completion.
 * On success, store channel-path inक्रमmation in @info and वापस 0. Return
 * non-zero otherwise.
 */
पूर्णांक sclp_chp_पढ़ो_info(काष्ठा sclp_chp_info *info)
अणु
	काष्ठा chp_info_sccb *sccb;
	पूर्णांक rc;

	अगर (!SCLP_HAS_CHP_INFO)
		वापस -EOPNOTSUPP;
	/* Prepare sccb. */
	sccb = (काष्ठा chp_info_sccb *) get_zeroed_page(GFP_KERNEL | GFP_DMA);
	अगर (!sccb)
		वापस -ENOMEM;
	sccb->header.length = माप(*sccb);
	rc = sclp_sync_request(SCLP_CMDW_READ_CHPATH_INFORMATION, sccb);
	अगर (rc)
		जाओ out;
	अगर (sccb->header.response_code != 0x0010) अणु
		pr_warn("read channel-path info failed (response=0x%04x)\n",
			sccb->header.response_code);
		rc = -EIO;
		जाओ out;
	पूर्ण
	स_नकल(info->recognized, sccb->recognized, SCLP_CHP_INFO_MASK_SIZE);
	स_नकल(info->standby, sccb->standby, SCLP_CHP_INFO_MASK_SIZE);
	स_नकल(info->configured, sccb->configured, SCLP_CHP_INFO_MASK_SIZE);
out:
	मुक्त_page((अचिन्हित दीर्घ) sccb);
	वापस rc;
पूर्ण

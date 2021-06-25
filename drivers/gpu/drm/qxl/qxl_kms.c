<शैली गुरु>
/*
 * Copyright 2013 Red Hat Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Dave Airlie
 *          Alon Levy
 */

#समावेश <linux/io-mapping.h>
#समावेश <linux/pci.h>

#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "qxl_drv.h"
#समावेश "qxl_object.h"

पूर्णांक qxl_log_level;

अटल bool qxl_check_device(काष्ठा qxl_device *qdev)
अणु
	काष्ठा qxl_rom *rom = qdev->rom;

	अगर (rom->magic != 0x4f525851) अणु
		DRM_ERROR("bad rom signature %x\n", rom->magic);
		वापस false;
	पूर्ण

	DRM_INFO("Device Version %d.%d\n", rom->id, rom->update_id);
	DRM_INFO("Compression level %d log level %d\n", rom->compression_level,
		 rom->log_level);
	DRM_INFO("%d io pages at offset 0x%x\n",
		 rom->num_io_pages, rom->pages_offset);
	DRM_INFO("%d byte draw area at offset 0x%x\n",
		 rom->surface0_area_size, rom->draw_area_offset);

	qdev->vram_size = rom->surface0_area_size;
	DRM_INFO("RAM header offset: 0x%x\n", rom->ram_header_offset);
	वापस true;
पूर्ण

अटल व्योम setup_hw_slot(काष्ठा qxl_device *qdev, काष्ठा qxl_memslot *slot)
अणु
	qdev->ram_header->mem_slot.mem_start = slot->start_phys_addr;
	qdev->ram_header->mem_slot.mem_end = slot->start_phys_addr + slot->size;
	qxl_io_memslot_add(qdev, qdev->rom->slots_start + slot->index);
पूर्ण

अटल व्योम setup_slot(काष्ठा qxl_device *qdev,
		       काष्ठा qxl_memslot *slot,
		       अचिन्हित पूर्णांक slot_index,
		       स्थिर अक्षर *slot_name,
		       अचिन्हित दीर्घ start_phys_addr,
		       अचिन्हित दीर्घ size)
अणु
	uपूर्णांक64_t high_bits;

	slot->index = slot_index;
	slot->name = slot_name;
	slot->start_phys_addr = start_phys_addr;
	slot->size = size;

	setup_hw_slot(qdev, slot);

	slot->generation = qdev->rom->slot_generation;
	high_bits = (qdev->rom->slots_start + slot->index)
		<< qdev->rom->slot_gen_bits;
	high_bits |= slot->generation;
	high_bits <<= (64 - (qdev->rom->slot_gen_bits + qdev->rom->slot_id_bits));
	slot->high_bits = high_bits;

	DRM_INFO("slot %d (%s): base 0x%08lx, size 0x%08lx\n",
		 slot->index, slot->name,
		 (अचिन्हित दीर्घ)slot->start_phys_addr,
		 (अचिन्हित दीर्घ)slot->size);
पूर्ण

व्योम qxl_reinit_memslots(काष्ठा qxl_device *qdev)
अणु
	setup_hw_slot(qdev, &qdev->मुख्य_slot);
	setup_hw_slot(qdev, &qdev->surfaces_slot);
पूर्ण

अटल व्योम qxl_gc_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qxl_device *qdev = container_of(work, काष्ठा qxl_device, gc_work);

	qxl_garbage_collect(qdev);
पूर्ण

पूर्णांक qxl_device_init(काष्ठा qxl_device *qdev,
		    काष्ठा pci_dev *pdev)
अणु
	पूर्णांक r, sb;

	pci_set_drvdata(pdev, &qdev->ddev);

	mutex_init(&qdev->gem.mutex);
	mutex_init(&qdev->update_area_mutex);
	mutex_init(&qdev->release_mutex);
	mutex_init(&qdev->surf_evict_mutex);
	qxl_gem_init(qdev);

	qdev->rom_base = pci_resource_start(pdev, 2);
	qdev->rom_size = pci_resource_len(pdev, 2);
	qdev->vram_base = pci_resource_start(pdev, 0);
	qdev->io_base = pci_resource_start(pdev, 3);

	qdev->vram_mapping = io_mapping_create_wc(qdev->vram_base, pci_resource_len(pdev, 0));
	अगर (!qdev->vram_mapping) अणु
		pr_err("Unable to create vram_mapping");
		वापस -ENOMEM;
	पूर्ण

	अगर (pci_resource_len(pdev, 4) > 0) अणु
		/* 64bit surface bar present */
		sb = 4;
		qdev->surfaceram_base = pci_resource_start(pdev, sb);
		qdev->surfaceram_size = pci_resource_len(pdev, sb);
		qdev->surface_mapping =
			io_mapping_create_wc(qdev->surfaceram_base,
					     qdev->surfaceram_size);
	पूर्ण
	अगर (qdev->surface_mapping == शून्य) अणु
		/* 64bit surface bar not present (or mapping failed) */
		sb = 1;
		qdev->surfaceram_base = pci_resource_start(pdev, sb);
		qdev->surfaceram_size = pci_resource_len(pdev, sb);
		qdev->surface_mapping =
			io_mapping_create_wc(qdev->surfaceram_base,
					     qdev->surfaceram_size);
		अगर (!qdev->surface_mapping) अणु
			pr_err("Unable to create surface_mapping");
			r = -ENOMEM;
			जाओ vram_mapping_मुक्त;
		पूर्ण
	पूर्ण

	DRM_DEBUG_KMS("qxl: vram %llx-%llx(%dM %dk), surface %llx-%llx(%dM %dk, %s)\n",
		 (अचिन्हित दीर्घ दीर्घ)qdev->vram_base,
		 (अचिन्हित दीर्घ दीर्घ)pci_resource_end(pdev, 0),
		 (पूर्णांक)pci_resource_len(pdev, 0) / 1024 / 1024,
		 (पूर्णांक)pci_resource_len(pdev, 0) / 1024,
		 (अचिन्हित दीर्घ दीर्घ)qdev->surfaceram_base,
		 (अचिन्हित दीर्घ दीर्घ)pci_resource_end(pdev, sb),
		 (पूर्णांक)qdev->surfaceram_size / 1024 / 1024,
		 (पूर्णांक)qdev->surfaceram_size / 1024,
		 (sb == 4) ? "64bit" : "32bit");

	qdev->rom = ioremap(qdev->rom_base, qdev->rom_size);
	अगर (!qdev->rom) अणु
		pr_err("Unable to ioremap ROM\n");
		r = -ENOMEM;
		जाओ surface_mapping_मुक्त;
	पूर्ण

	अगर (!qxl_check_device(qdev)) अणु
		r = -ENODEV;
		जाओ rom_unmap;
	पूर्ण

	r = qxl_bo_init(qdev);
	अगर (r) अणु
		DRM_ERROR("bo init failed %d\n", r);
		जाओ rom_unmap;
	पूर्ण

	qdev->ram_header = ioremap(qdev->vram_base +
				   qdev->rom->ram_header_offset,
				   माप(*qdev->ram_header));
	अगर (!qdev->ram_header) अणु
		DRM_ERROR("Unable to ioremap RAM header\n");
		r = -ENOMEM;
		जाओ bo_fini;
	पूर्ण

	qdev->command_ring = qxl_ring_create(&(qdev->ram_header->cmd_ring_hdr),
					     माप(काष्ठा qxl_command),
					     QXL_COMMAND_RING_SIZE,
					     qdev->io_base + QXL_IO_NOTIFY_CMD,
					     false,
					     &qdev->display_event);
	अगर (!qdev->command_ring) अणु
		DRM_ERROR("Unable to create command ring\n");
		r = -ENOMEM;
		जाओ ram_header_unmap;
	पूर्ण

	qdev->cursor_ring = qxl_ring_create(
				&(qdev->ram_header->cursor_ring_hdr),
				माप(काष्ठा qxl_command),
				QXL_CURSOR_RING_SIZE,
				qdev->io_base + QXL_IO_NOTIFY_CURSOR,
				false,
				&qdev->cursor_event);

	अगर (!qdev->cursor_ring) अणु
		DRM_ERROR("Unable to create cursor ring\n");
		r = -ENOMEM;
		जाओ command_ring_मुक्त;
	पूर्ण

	qdev->release_ring = qxl_ring_create(
				&(qdev->ram_header->release_ring_hdr),
				माप(uपूर्णांक64_t),
				QXL_RELEASE_RING_SIZE, 0, true,
				शून्य);

	अगर (!qdev->release_ring) अणु
		DRM_ERROR("Unable to create release ring\n");
		r = -ENOMEM;
		जाओ cursor_ring_मुक्त;
	पूर्ण

	idr_init_base(&qdev->release_idr, 1);
	spin_lock_init(&qdev->release_idr_lock);
	spin_lock_init(&qdev->release_lock);

	idr_init_base(&qdev->surf_id_idr, 1);
	spin_lock_init(&qdev->surf_id_idr_lock);

	mutex_init(&qdev->async_io_mutex);

	/* reset the device पूर्णांकo a known state - no memslots, no primary
	 * created, no surfaces. */
	qxl_io_reset(qdev);

	/* must initialize irq beक्रमe first async io - slot creation */
	r = qxl_irq_init(qdev);
	अगर (r) अणु
		DRM_ERROR("Unable to init qxl irq\n");
		जाओ release_ring_मुक्त;
	पूर्ण

	/*
	 * Note that भव is surface0. We rely on the single ioremap करोne
	 * beक्रमe.
	 */
	setup_slot(qdev, &qdev->मुख्य_slot, 0, "main",
		   (अचिन्हित दीर्घ)qdev->vram_base,
		   (अचिन्हित दीर्घ)qdev->rom->ram_header_offset);
	setup_slot(qdev, &qdev->surfaces_slot, 1, "surfaces",
		   (अचिन्हित दीर्घ)qdev->surfaceram_base,
		   (अचिन्हित दीर्घ)qdev->surfaceram_size);

	INIT_WORK(&qdev->gc_work, qxl_gc_work);

	वापस 0;

release_ring_मुक्त:
	qxl_ring_मुक्त(qdev->release_ring);
cursor_ring_मुक्त:
	qxl_ring_मुक्त(qdev->cursor_ring);
command_ring_मुक्त:
	qxl_ring_मुक्त(qdev->command_ring);
ram_header_unmap:
	iounmap(qdev->ram_header);
bo_fini:
	qxl_bo_fini(qdev);
rom_unmap:
	iounmap(qdev->rom);
surface_mapping_मुक्त:
	io_mapping_मुक्त(qdev->surface_mapping);
vram_mapping_मुक्त:
	io_mapping_मुक्त(qdev->vram_mapping);
	वापस r;
पूर्ण

व्योम qxl_device_fini(काष्ठा qxl_device *qdev)
अणु
	पूर्णांक cur_idx;

	/* check अगर qxl_device_init() was successful (gc_work is initialized last) */
	अगर (!qdev->gc_work.func)
		वापस;

	क्रम (cur_idx = 0; cur_idx < 3; cur_idx++) अणु
		अगर (!qdev->current_release_bo[cur_idx])
			जारी;
		qxl_bo_unpin(qdev->current_release_bo[cur_idx]);
		qxl_bo_unref(&qdev->current_release_bo[cur_idx]);
		qdev->current_release_bo_offset[cur_idx] = 0;
		qdev->current_release_bo[cur_idx] = शून्य;
	पूर्ण

	/*
	 * Ask host to release resources (+fill release ring),
	 * then रुको क्रम the release actually happening.
	 */
	qxl_io_notअगरy_oom(qdev);
	रुको_event_समयout(qdev->release_event,
			   atomic_पढ़ो(&qdev->release_count) == 0,
			   HZ);
	flush_work(&qdev->gc_work);
	qxl_surf_evict(qdev);
	qxl_vram_evict(qdev);

	qxl_gem_fini(qdev);
	qxl_bo_fini(qdev);
	qxl_ring_मुक्त(qdev->command_ring);
	qxl_ring_मुक्त(qdev->cursor_ring);
	qxl_ring_मुक्त(qdev->release_ring);
	io_mapping_मुक्त(qdev->surface_mapping);
	io_mapping_मुक्त(qdev->vram_mapping);
	iounmap(qdev->ram_header);
	iounmap(qdev->rom);
	qdev->rom = शून्य;
पूर्ण

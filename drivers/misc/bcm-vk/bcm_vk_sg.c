<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2018-2020 Broadcom.
 */
#समावेश <linux/dma-mapping.h>
#समावेश <linux/mm.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/pgtable.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <uapi/linux/misc/bcm_vk.h>

#समावेश "bcm_vk.h"
#समावेश "bcm_vk_msg.h"
#समावेश "bcm_vk_sg.h"

/*
 * Valkyrie has a hardware limitation of 16M transfer size.
 * So limit the SGL chunks to 16M.
 */
#घोषणा BCM_VK_MAX_SGL_CHUNK SZ_16M

अटल पूर्णांक bcm_vk_dma_alloc(काष्ठा device *dev,
			    काष्ठा bcm_vk_dma *dma,
			    पूर्णांक dir,
			    काष्ठा _vk_data *vkdata);
अटल पूर्णांक bcm_vk_dma_मुक्त(काष्ठा device *dev, काष्ठा bcm_vk_dma *dma);

/* Uncomment to dump SGLIST */
/* #घोषणा BCM_VK_DUMP_SGLIST */

अटल पूर्णांक bcm_vk_dma_alloc(काष्ठा device *dev,
			    काष्ठा bcm_vk_dma *dma,
			    पूर्णांक direction,
			    काष्ठा _vk_data *vkdata)
अणु
	dma_addr_t addr, sg_addr;
	पूर्णांक err;
	पूर्णांक i;
	पूर्णांक offset;
	u32 size;
	u32 reमुख्यing_size;
	u32 transfer_size;
	u64 data;
	अचिन्हित दीर्घ first, last;
	काष्ठा _vk_data *sgdata;

	/* Get 64-bit user address */
	data = get_unaligned(&vkdata->address);

	/* offset पूर्णांकo first page */
	offset = offset_in_page(data);

	/* Calculate number of pages */
	first = (data & PAGE_MASK) >> PAGE_SHIFT;
	last  = ((data + vkdata->size - 1) & PAGE_MASK) >> PAGE_SHIFT;
	dma->nr_pages = last - first + 1;

	/* Allocate DMA pages */
	dma->pages = kदो_स्मृति_array(dma->nr_pages,
				   माप(काष्ठा page *),
				   GFP_KERNEL);
	अगर (!dma->pages)
		वापस -ENOMEM;

	dev_dbg(dev, "Alloc DMA Pages [0x%llx+0x%x => %d pages]\n",
		data, vkdata->size, dma->nr_pages);

	dma->direction = direction;

	/* Get user pages पूर्णांकo memory */
	err = get_user_pages_fast(data & PAGE_MASK,
				  dma->nr_pages,
				  direction == DMA_FROM_DEVICE,
				  dma->pages);
	अगर (err != dma->nr_pages) अणु
		dma->nr_pages = (err >= 0) ? err : 0;
		dev_err(dev, "get_user_pages_fast, err=%d [%d]\n",
			err, dma->nr_pages);
		वापस err < 0 ? err : -EINVAL;
	पूर्ण

	/* Max size of sg list is 1 per mapped page + fields at start */
	dma->sglen = (dma->nr_pages * माप(*sgdata)) +
		     (माप(u32) * SGLIST_VKDATA_START);

	/* Allocate sglist */
	dma->sglist = dma_alloc_coherent(dev,
					 dma->sglen,
					 &dma->handle,
					 GFP_KERNEL);
	अगर (!dma->sglist)
		वापस -ENOMEM;

	dma->sglist[SGLIST_NUM_SG] = 0;
	dma->sglist[SGLIST_TOTALSIZE] = vkdata->size;
	reमुख्यing_size = vkdata->size;
	sgdata = (काष्ठा _vk_data *)&dma->sglist[SGLIST_VKDATA_START];

	/* Map all pages पूर्णांकo DMA */
	size = min_t(माप_प्रकार, PAGE_SIZE - offset, reमुख्यing_size);
	reमुख्यing_size -= size;
	sg_addr = dma_map_page(dev,
			       dma->pages[0],
			       offset,
			       size,
			       dma->direction);
	transfer_size = size;
	अगर (unlikely(dma_mapping_error(dev, sg_addr))) अणु
		__मुक्त_page(dma->pages[0]);
		वापस -EIO;
	पूर्ण

	क्रम (i = 1; i < dma->nr_pages; i++) अणु
		size = min_t(माप_प्रकार, PAGE_SIZE, reमुख्यing_size);
		reमुख्यing_size -= size;
		addr = dma_map_page(dev,
				    dma->pages[i],
				    0,
				    size,
				    dma->direction);
		अगर (unlikely(dma_mapping_error(dev, addr))) अणु
			__मुक्त_page(dma->pages[i]);
			वापस -EIO;
		पूर्ण

		/*
		 * Compress SG list entry when pages are contiguous
		 * and transfer size less or equal to BCM_VK_MAX_SGL_CHUNK
		 */
		अगर ((addr == (sg_addr + transfer_size)) &&
		    ((transfer_size + size) <= BCM_VK_MAX_SGL_CHUNK)) अणु
			/* pages are contiguous, add to same sg entry */
			transfer_size += size;
		पूर्ण अन्यथा अणु
			/* pages are not contiguous, ग_लिखो sg entry */
			sgdata->size = transfer_size;
			put_unaligned(sg_addr, (u64 *)&sgdata->address);
			dma->sglist[SGLIST_NUM_SG]++;

			/* start new sg entry */
			sgdata++;
			sg_addr = addr;
			transfer_size = size;
		पूर्ण
	पूर्ण
	/* Write last sg list entry */
	sgdata->size = transfer_size;
	put_unaligned(sg_addr, (u64 *)&sgdata->address);
	dma->sglist[SGLIST_NUM_SG]++;

	/* Update poपूर्णांकers and size field to poपूर्णांक to sglist */
	put_unaligned((u64)dma->handle, &vkdata->address);
	vkdata->size = (dma->sglist[SGLIST_NUM_SG] * माप(*sgdata)) +
		       (माप(u32) * SGLIST_VKDATA_START);

#अगर_घोषित BCM_VK_DUMP_SGLIST
	dev_dbg(dev,
		"sgl 0x%llx handle 0x%llx, sglen: 0x%x sgsize: 0x%x\n",
		(u64)dma->sglist,
		dma->handle,
		dma->sglen,
		vkdata->size);
	क्रम (i = 0; i < vkdata->size / माप(u32); i++)
		dev_dbg(dev, "i:0x%x 0x%x\n", i, dma->sglist[i]);
#पूर्ण_अगर

	वापस 0;
पूर्ण

पूर्णांक bcm_vk_sg_alloc(काष्ठा device *dev,
		    काष्ठा bcm_vk_dma *dma,
		    पूर्णांक dir,
		    काष्ठा _vk_data *vkdata,
		    पूर्णांक num)
अणु
	पूर्णांक i;
	पूर्णांक rc = -EINVAL;

	/* Convert user addresses to DMA SG List */
	क्रम (i = 0; i < num; i++) अणु
		अगर (vkdata[i].size && vkdata[i].address) अणु
			/*
			 * If both size and address are non-zero
			 * then DMA alloc.
			 */
			rc = bcm_vk_dma_alloc(dev,
					      &dma[i],
					      dir,
					      &vkdata[i]);
		पूर्ण अन्यथा अगर (vkdata[i].size ||
			   vkdata[i].address) अणु
			/*
			 * If one of size and address are zero
			 * there is a problem.
			 */
			dev_err(dev,
				"Invalid vkdata %x 0x%x 0x%llx\n",
				i, vkdata[i].size, vkdata[i].address);
			rc = -EINVAL;
		पूर्ण अन्यथा अणु
			/*
			 * If size and address are both zero
			 * करोn't convert, but वापस success.
			 */
			rc = 0;
		पूर्ण

		अगर (rc)
			जाओ fail_alloc;
	पूर्ण
	वापस rc;

fail_alloc:
	जबतक (i > 0) अणु
		i--;
		अगर (dma[i].sglist)
			bcm_vk_dma_मुक्त(dev, &dma[i]);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक bcm_vk_dma_मुक्त(काष्ठा device *dev, काष्ठा bcm_vk_dma *dma)
अणु
	dma_addr_t addr;
	पूर्णांक i;
	पूर्णांक num_sg;
	u32 size;
	काष्ठा _vk_data *vkdata;

	dev_dbg(dev, "free sglist=%p sglen=0x%x\n", dma->sglist, dma->sglen);

	/* Unmap all pages in the sglist */
	num_sg = dma->sglist[SGLIST_NUM_SG];
	vkdata = (काष्ठा _vk_data *)&dma->sglist[SGLIST_VKDATA_START];
	क्रम (i = 0; i < num_sg; i++) अणु
		size = vkdata[i].size;
		addr = get_unaligned(&vkdata[i].address);

		dma_unmap_page(dev, addr, size, dma->direction);
	पूर्ण

	/* Free allocated sglist */
	dma_मुक्त_coherent(dev, dma->sglen, dma->sglist, dma->handle);

	/* Release lock on all pages */
	क्रम (i = 0; i < dma->nr_pages; i++)
		put_page(dma->pages[i]);

	/* Free allocated dma pages */
	kमुक्त(dma->pages);
	dma->sglist = शून्य;

	वापस 0;
पूर्ण

पूर्णांक bcm_vk_sg_मुक्त(काष्ठा device *dev, काष्ठा bcm_vk_dma *dma, पूर्णांक num,
		   पूर्णांक *proc_cnt)
अणु
	पूर्णांक i;

	*proc_cnt = 0;
	/* Unmap and मुक्त all pages and sglists */
	क्रम (i = 0; i < num; i++) अणु
		अगर (dma[i].sglist) अणु
			bcm_vk_dma_मुक्त(dev, &dma[i]);
			*proc_cnt += 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VPDMA helper library
 *
 * Copyright (c) 2013 Texas Instruments Inc.
 *
 * David Griego, <dagriego@biglakesoftware.com>
 * Dale Farnsworth, <dale@farnsworth.org>
 * Archit Taneja, <archit@ti.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/firmware.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>

#समावेश "vpdma.h"
#समावेश "vpdma_priv.h"

#घोषणा VPDMA_FIRMWARE	"vpdma-1b8.bin"

स्थिर काष्ठा vpdma_data_क्रमmat vpdma_yuv_fmts[] = अणु
	[VPDMA_DATA_FMT_Y444] = अणु
		.type		= VPDMA_DATA_FMT_TYPE_YUV,
		.data_type	= DATA_TYPE_Y444,
		.depth		= 8,
	पूर्ण,
	[VPDMA_DATA_FMT_Y422] = अणु
		.type		= VPDMA_DATA_FMT_TYPE_YUV,
		.data_type	= DATA_TYPE_Y422,
		.depth		= 8,
	पूर्ण,
	[VPDMA_DATA_FMT_Y420] = अणु
		.type		= VPDMA_DATA_FMT_TYPE_YUV,
		.data_type	= DATA_TYPE_Y420,
		.depth		= 8,
	पूर्ण,
	[VPDMA_DATA_FMT_C444] = अणु
		.type		= VPDMA_DATA_FMT_TYPE_YUV,
		.data_type	= DATA_TYPE_C444,
		.depth		= 8,
	पूर्ण,
	[VPDMA_DATA_FMT_C422] = अणु
		.type		= VPDMA_DATA_FMT_TYPE_YUV,
		.data_type	= DATA_TYPE_C422,
		.depth		= 8,
	पूर्ण,
	[VPDMA_DATA_FMT_C420] = अणु
		.type		= VPDMA_DATA_FMT_TYPE_YUV,
		.data_type	= DATA_TYPE_C420,
		.depth		= 4,
	पूर्ण,
	[VPDMA_DATA_FMT_CB420] = अणु
		.type		= VPDMA_DATA_FMT_TYPE_YUV,
		.data_type	= DATA_TYPE_CB420,
		.depth		= 4,
	पूर्ण,
	[VPDMA_DATA_FMT_YCR422] = अणु
		.type		= VPDMA_DATA_FMT_TYPE_YUV,
		.data_type	= DATA_TYPE_YCR422,
		.depth		= 16,
	पूर्ण,
	[VPDMA_DATA_FMT_YC444] = अणु
		.type		= VPDMA_DATA_FMT_TYPE_YUV,
		.data_type	= DATA_TYPE_YC444,
		.depth		= 24,
	पूर्ण,
	[VPDMA_DATA_FMT_CRY422] = अणु
		.type		= VPDMA_DATA_FMT_TYPE_YUV,
		.data_type	= DATA_TYPE_CRY422,
		.depth		= 16,
	पूर्ण,
	[VPDMA_DATA_FMT_CBY422] = अणु
		.type		= VPDMA_DATA_FMT_TYPE_YUV,
		.data_type	= DATA_TYPE_CBY422,
		.depth		= 16,
	पूर्ण,
	[VPDMA_DATA_FMT_YCB422] = अणु
		.type		= VPDMA_DATA_FMT_TYPE_YUV,
		.data_type	= DATA_TYPE_YCB422,
		.depth		= 16,
	पूर्ण,
पूर्ण;
EXPORT_SYMBOL(vpdma_yuv_fmts);

स्थिर काष्ठा vpdma_data_क्रमmat vpdma_rgb_fmts[] = अणु
	[VPDMA_DATA_FMT_RGB565] = अणु
		.type		= VPDMA_DATA_FMT_TYPE_RGB,
		.data_type	= DATA_TYPE_RGB16_565,
		.depth		= 16,
	पूर्ण,
	[VPDMA_DATA_FMT_ARGB16_1555] = अणु
		.type		= VPDMA_DATA_FMT_TYPE_RGB,
		.data_type	= DATA_TYPE_ARGB_1555,
		.depth		= 16,
	पूर्ण,
	[VPDMA_DATA_FMT_ARGB16] = अणु
		.type		= VPDMA_DATA_FMT_TYPE_RGB,
		.data_type	= DATA_TYPE_ARGB_4444,
		.depth		= 16,
	पूर्ण,
	[VPDMA_DATA_FMT_RGBA16_5551] = अणु
		.type		= VPDMA_DATA_FMT_TYPE_RGB,
		.data_type	= DATA_TYPE_RGBA_5551,
		.depth		= 16,
	पूर्ण,
	[VPDMA_DATA_FMT_RGBA16] = अणु
		.type		= VPDMA_DATA_FMT_TYPE_RGB,
		.data_type	= DATA_TYPE_RGBA_4444,
		.depth		= 16,
	पूर्ण,
	[VPDMA_DATA_FMT_ARGB24] = अणु
		.type		= VPDMA_DATA_FMT_TYPE_RGB,
		.data_type	= DATA_TYPE_ARGB24_6666,
		.depth		= 24,
	पूर्ण,
	[VPDMA_DATA_FMT_RGB24] = अणु
		.type		= VPDMA_DATA_FMT_TYPE_RGB,
		.data_type	= DATA_TYPE_RGB24_888,
		.depth		= 24,
	पूर्ण,
	[VPDMA_DATA_FMT_ARGB32] = अणु
		.type		= VPDMA_DATA_FMT_TYPE_RGB,
		.data_type	= DATA_TYPE_ARGB32_8888,
		.depth		= 32,
	पूर्ण,
	[VPDMA_DATA_FMT_RGBA24] = अणु
		.type		= VPDMA_DATA_FMT_TYPE_RGB,
		.data_type	= DATA_TYPE_RGBA24_6666,
		.depth		= 24,
	पूर्ण,
	[VPDMA_DATA_FMT_RGBA32] = अणु
		.type		= VPDMA_DATA_FMT_TYPE_RGB,
		.data_type	= DATA_TYPE_RGBA32_8888,
		.depth		= 32,
	पूर्ण,
	[VPDMA_DATA_FMT_BGR565] = अणु
		.type		= VPDMA_DATA_FMT_TYPE_RGB,
		.data_type	= DATA_TYPE_BGR16_565,
		.depth		= 16,
	पूर्ण,
	[VPDMA_DATA_FMT_ABGR16_1555] = अणु
		.type		= VPDMA_DATA_FMT_TYPE_RGB,
		.data_type	= DATA_TYPE_ABGR_1555,
		.depth		= 16,
	पूर्ण,
	[VPDMA_DATA_FMT_ABGR16] = अणु
		.type		= VPDMA_DATA_FMT_TYPE_RGB,
		.data_type	= DATA_TYPE_ABGR_4444,
		.depth		= 16,
	पूर्ण,
	[VPDMA_DATA_FMT_BGRA16_5551] = अणु
		.type		= VPDMA_DATA_FMT_TYPE_RGB,
		.data_type	= DATA_TYPE_BGRA_5551,
		.depth		= 16,
	पूर्ण,
	[VPDMA_DATA_FMT_BGRA16] = अणु
		.type		= VPDMA_DATA_FMT_TYPE_RGB,
		.data_type	= DATA_TYPE_BGRA_4444,
		.depth		= 16,
	पूर्ण,
	[VPDMA_DATA_FMT_ABGR24] = अणु
		.type		= VPDMA_DATA_FMT_TYPE_RGB,
		.data_type	= DATA_TYPE_ABGR24_6666,
		.depth		= 24,
	पूर्ण,
	[VPDMA_DATA_FMT_BGR24] = अणु
		.type		= VPDMA_DATA_FMT_TYPE_RGB,
		.data_type	= DATA_TYPE_BGR24_888,
		.depth		= 24,
	पूर्ण,
	[VPDMA_DATA_FMT_ABGR32] = अणु
		.type		= VPDMA_DATA_FMT_TYPE_RGB,
		.data_type	= DATA_TYPE_ABGR32_8888,
		.depth		= 32,
	पूर्ण,
	[VPDMA_DATA_FMT_BGRA24] = अणु
		.type		= VPDMA_DATA_FMT_TYPE_RGB,
		.data_type	= DATA_TYPE_BGRA24_6666,
		.depth		= 24,
	पूर्ण,
	[VPDMA_DATA_FMT_BGRA32] = अणु
		.type		= VPDMA_DATA_FMT_TYPE_RGB,
		.data_type	= DATA_TYPE_BGRA32_8888,
		.depth		= 32,
	पूर्ण,
पूर्ण;
EXPORT_SYMBOL(vpdma_rgb_fmts);

/*
 * To handle RAW क्रमmat we are re-using the CBY422
 * vpdma data type so that we use the vpdma to re-order
 * the incoming bytes, as the parser assumes that the
 * first byte presented on the bus is the MSB of a 2
 * bytes value.
 * RAW8 handles from 1 to 8 bits
 * RAW16 handles from 9 to 16 bits
 */
स्थिर काष्ठा vpdma_data_क्रमmat vpdma_raw_fmts[] = अणु
	[VPDMA_DATA_FMT_RAW8] = अणु
		.type		= VPDMA_DATA_FMT_TYPE_YUV,
		.data_type	= DATA_TYPE_CBY422,
		.depth		= 8,
	पूर्ण,
	[VPDMA_DATA_FMT_RAW16] = अणु
		.type		= VPDMA_DATA_FMT_TYPE_YUV,
		.data_type	= DATA_TYPE_CBY422,
		.depth		= 16,
	पूर्ण,
पूर्ण;
EXPORT_SYMBOL(vpdma_raw_fmts);

स्थिर काष्ठा vpdma_data_क्रमmat vpdma_misc_fmts[] = अणु
	[VPDMA_DATA_FMT_MV] = अणु
		.type		= VPDMA_DATA_FMT_TYPE_MISC,
		.data_type	= DATA_TYPE_MV,
		.depth		= 4,
	पूर्ण,
पूर्ण;
EXPORT_SYMBOL(vpdma_misc_fmts);

काष्ठा vpdma_channel_info अणु
	पूर्णांक num;		/* VPDMA channel number */
	पूर्णांक cstat_offset;	/* client CSTAT रेजिस्टर offset */
पूर्ण;

अटल स्थिर काष्ठा vpdma_channel_info chan_info[] = अणु
	[VPE_CHAN_LUMA1_IN] = अणु
		.num		= VPE_CHAN_NUM_LUMA1_IN,
		.cstat_offset	= VPDMA_DEI_LUMA1_CSTAT,
	पूर्ण,
	[VPE_CHAN_CHROMA1_IN] = अणु
		.num		= VPE_CHAN_NUM_CHROMA1_IN,
		.cstat_offset	= VPDMA_DEI_CHROMA1_CSTAT,
	पूर्ण,
	[VPE_CHAN_LUMA2_IN] = अणु
		.num		= VPE_CHAN_NUM_LUMA2_IN,
		.cstat_offset	= VPDMA_DEI_LUMA2_CSTAT,
	पूर्ण,
	[VPE_CHAN_CHROMA2_IN] = अणु
		.num		= VPE_CHAN_NUM_CHROMA2_IN,
		.cstat_offset	= VPDMA_DEI_CHROMA2_CSTAT,
	पूर्ण,
	[VPE_CHAN_LUMA3_IN] = अणु
		.num		= VPE_CHAN_NUM_LUMA3_IN,
		.cstat_offset	= VPDMA_DEI_LUMA3_CSTAT,
	पूर्ण,
	[VPE_CHAN_CHROMA3_IN] = अणु
		.num		= VPE_CHAN_NUM_CHROMA3_IN,
		.cstat_offset	= VPDMA_DEI_CHROMA3_CSTAT,
	पूर्ण,
	[VPE_CHAN_MV_IN] = अणु
		.num		= VPE_CHAN_NUM_MV_IN,
		.cstat_offset	= VPDMA_DEI_MV_IN_CSTAT,
	पूर्ण,
	[VPE_CHAN_MV_OUT] = अणु
		.num		= VPE_CHAN_NUM_MV_OUT,
		.cstat_offset	= VPDMA_DEI_MV_OUT_CSTAT,
	पूर्ण,
	[VPE_CHAN_LUMA_OUT] = अणु
		.num		= VPE_CHAN_NUM_LUMA_OUT,
		.cstat_offset	= VPDMA_VIP_UP_Y_CSTAT,
	पूर्ण,
	[VPE_CHAN_CHROMA_OUT] = अणु
		.num		= VPE_CHAN_NUM_CHROMA_OUT,
		.cstat_offset	= VPDMA_VIP_UP_UV_CSTAT,
	पूर्ण,
	[VPE_CHAN_RGB_OUT] = अणु
		.num		= VPE_CHAN_NUM_RGB_OUT,
		.cstat_offset	= VPDMA_VIP_UP_Y_CSTAT,
	पूर्ण,
पूर्ण;

अटल u32 पढ़ो_reg(काष्ठा vpdma_data *vpdma, पूर्णांक offset)
अणु
	वापस ioपढ़ो32(vpdma->base + offset);
पूर्ण

अटल व्योम ग_लिखो_reg(काष्ठा vpdma_data *vpdma, पूर्णांक offset, u32 value)
अणु
	ioग_लिखो32(value, vpdma->base + offset);
पूर्ण

अटल पूर्णांक पढ़ो_field_reg(काष्ठा vpdma_data *vpdma, पूर्णांक offset,
		u32 mask, पूर्णांक shअगरt)
अणु
	वापस (पढ़ो_reg(vpdma, offset) & (mask << shअगरt)) >> shअगरt;
पूर्ण

अटल व्योम ग_लिखो_field_reg(काष्ठा vpdma_data *vpdma, पूर्णांक offset, u32 field,
		u32 mask, पूर्णांक shअगरt)
अणु
	u32 val = पढ़ो_reg(vpdma, offset);

	val &= ~(mask << shअगरt);
	val |= (field & mask) << shअगरt;

	ग_लिखो_reg(vpdma, offset, val);
पूर्ण

व्योम vpdma_dump_regs(काष्ठा vpdma_data *vpdma)
अणु
	काष्ठा device *dev = &vpdma->pdev->dev;

#घोषणा DUMPREG(r) dev_dbg(dev, "%-35s %08x\n", #r, पढ़ो_reg(vpdma, VPDMA_##r))

	dev_dbg(dev, "VPDMA Registers:\n");

	DUMPREG(PID);
	DUMPREG(LIST_ADDR);
	DUMPREG(LIST_ATTR);
	DUMPREG(LIST_STAT_SYNC);
	DUMPREG(BG_RGB);
	DUMPREG(BG_YUV);
	DUMPREG(SETUP);
	DUMPREG(MAX_SIZE1);
	DUMPREG(MAX_SIZE2);
	DUMPREG(MAX_SIZE3);

	/*
	 * dumping रेजिस्टरs of only group0 and group3, because VPE channels
	 * lie within group0 and group3 रेजिस्टरs
	 */
	DUMPREG(INT_CHAN_STAT(0));
	DUMPREG(INT_CHAN_MASK(0));
	DUMPREG(INT_CHAN_STAT(3));
	DUMPREG(INT_CHAN_MASK(3));
	DUMPREG(INT_CLIENT0_STAT);
	DUMPREG(INT_CLIENT0_MASK);
	DUMPREG(INT_CLIENT1_STAT);
	DUMPREG(INT_CLIENT1_MASK);
	DUMPREG(INT_LIST0_STAT);
	DUMPREG(INT_LIST0_MASK);

	/*
	 * these are रेजिस्टरs specअगरic to VPE clients, we can make this
	 * function dump client रेजिस्टरs specअगरic to VPE or VIP based on
	 * who is using it
	 */
	DUMPREG(DEI_CHROMA1_CSTAT);
	DUMPREG(DEI_LUMA1_CSTAT);
	DUMPREG(DEI_CHROMA2_CSTAT);
	DUMPREG(DEI_LUMA2_CSTAT);
	DUMPREG(DEI_CHROMA3_CSTAT);
	DUMPREG(DEI_LUMA3_CSTAT);
	DUMPREG(DEI_MV_IN_CSTAT);
	DUMPREG(DEI_MV_OUT_CSTAT);
	DUMPREG(VIP_UP_Y_CSTAT);
	DUMPREG(VIP_UP_UV_CSTAT);
	DUMPREG(VPI_CTL_CSTAT);
पूर्ण
EXPORT_SYMBOL(vpdma_dump_regs);

/*
 * Allocate a DMA buffer
 */
पूर्णांक vpdma_alloc_desc_buf(काष्ठा vpdma_buf *buf, माप_प्रकार size)
अणु
	buf->size = size;
	buf->mapped = false;
	buf->addr = kzalloc(size, GFP_KERNEL);
	अगर (!buf->addr)
		वापस -ENOMEM;

	WARN_ON(((अचिन्हित दीर्घ)buf->addr & VPDMA_DESC_ALIGN) != 0);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(vpdma_alloc_desc_buf);

व्योम vpdma_मुक्त_desc_buf(काष्ठा vpdma_buf *buf)
अणु
	WARN_ON(buf->mapped);
	kमुक्त(buf->addr);
	buf->addr = शून्य;
	buf->size = 0;
पूर्ण
EXPORT_SYMBOL(vpdma_मुक्त_desc_buf);

/*
 * map descriptor/payload DMA buffer, enabling DMA access
 */
पूर्णांक vpdma_map_desc_buf(काष्ठा vpdma_data *vpdma, काष्ठा vpdma_buf *buf)
अणु
	काष्ठा device *dev = &vpdma->pdev->dev;

	WARN_ON(buf->mapped);
	buf->dma_addr = dma_map_single(dev, buf->addr, buf->size,
				DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(dev, buf->dma_addr)) अणु
		dev_err(dev, "failed to map buffer\n");
		वापस -EINVAL;
	पूर्ण

	buf->mapped = true;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(vpdma_map_desc_buf);

/*
 * unmap descriptor/payload DMA buffer, disabling DMA access and
 * allowing the मुख्य processor to access the data
 */
व्योम vpdma_unmap_desc_buf(काष्ठा vpdma_data *vpdma, काष्ठा vpdma_buf *buf)
अणु
	काष्ठा device *dev = &vpdma->pdev->dev;

	अगर (buf->mapped)
		dma_unmap_single(dev, buf->dma_addr, buf->size,
				DMA_BIसूचीECTIONAL);

	buf->mapped = false;
पूर्ण
EXPORT_SYMBOL(vpdma_unmap_desc_buf);

/*
 * Cleanup all pending descriptors of a list
 * First, stop the current list being processed.
 * If the VPDMA was busy, this step makes vpdma to accept post lists.
 * To cleanup the पूर्णांकernal FSM, post पात list descriptor क्रम all the
 * channels from @channels array of size @size.
 */
पूर्णांक vpdma_list_cleanup(काष्ठा vpdma_data *vpdma, पूर्णांक list_num,
		पूर्णांक *channels, पूर्णांक size)
अणु
	काष्ठा vpdma_desc_list पात_list;
	पूर्णांक i, ret, समयout = 500;

	ग_लिखो_reg(vpdma, VPDMA_LIST_ATTR,
			(list_num << VPDMA_LIST_NUM_SHFT) |
			(1 << VPDMA_LIST_STOP_SHFT));

	अगर (size <= 0 || !channels)
		वापस 0;

	ret = vpdma_create_desc_list(&पात_list,
		size * माप(काष्ठा vpdma_dtd), VPDMA_LIST_TYPE_NORMAL);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < size; i++)
		vpdma_add_पात_channel_ctd(&पात_list, channels[i]);

	ret = vpdma_map_desc_buf(vpdma, &पात_list.buf);
	अगर (ret)
		जाओ मुक्त_desc;
	ret = vpdma_submit_descs(vpdma, &पात_list, list_num);
	अगर (ret)
		जाओ unmap_desc;

	जबतक (vpdma_list_busy(vpdma, list_num) && --समयout)
		;

	अगर (समयout == 0) अणु
		dev_err(&vpdma->pdev->dev, "Timed out cleaning up VPDMA list\n");
		ret = -EBUSY;
	पूर्ण

unmap_desc:
	vpdma_unmap_desc_buf(vpdma, &पात_list.buf);
मुक्त_desc:
	vpdma_मुक्त_desc_buf(&पात_list.buf);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(vpdma_list_cleanup);

/*
 * create a descriptor list, the user of this list will append configuration,
 * control and data descriptors to this list, this list will be submitted to
 * VPDMA. VPDMA's list parser will go through each descriptor and perक्रमm the
 * required DMA operations
 */
पूर्णांक vpdma_create_desc_list(काष्ठा vpdma_desc_list *list, माप_प्रकार size, पूर्णांक type)
अणु
	पूर्णांक r;

	r = vpdma_alloc_desc_buf(&list->buf, size);
	अगर (r)
		वापस r;

	list->next = list->buf.addr;

	list->type = type;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(vpdma_create_desc_list);

/*
 * once a descriptor list is parsed by VPDMA, we reset the list by emptying it,
 * to allow new descriptors to be added to the list.
 */
व्योम vpdma_reset_desc_list(काष्ठा vpdma_desc_list *list)
अणु
	list->next = list->buf.addr;
पूर्ण
EXPORT_SYMBOL(vpdma_reset_desc_list);

/*
 * मुक्त the buffer allocated क्रम the VPDMA descriptor list, this should be
 * called when the user करोesn't want to use VPDMA any more.
 */
व्योम vpdma_मुक्त_desc_list(काष्ठा vpdma_desc_list *list)
अणु
	vpdma_मुक्त_desc_buf(&list->buf);

	list->next = शून्य;
पूर्ण
EXPORT_SYMBOL(vpdma_मुक्त_desc_list);

bool vpdma_list_busy(काष्ठा vpdma_data *vpdma, पूर्णांक list_num)
अणु
	वापस पढ़ो_reg(vpdma, VPDMA_LIST_STAT_SYNC) & BIT(list_num + 16);
पूर्ण
EXPORT_SYMBOL(vpdma_list_busy);

/*
 * submit a list of DMA descriptors to the VPE VPDMA, करो not रुको क्रम completion
 */
पूर्णांक vpdma_submit_descs(काष्ठा vpdma_data *vpdma,
			काष्ठा vpdma_desc_list *list, पूर्णांक list_num)
अणु
	पूर्णांक list_size;
	अचिन्हित दीर्घ flags;

	अगर (vpdma_list_busy(vpdma, list_num))
		वापस -EBUSY;

	/* 16-byte granularity */
	list_size = (list->next - list->buf.addr) >> 4;

	spin_lock_irqsave(&vpdma->lock, flags);
	ग_लिखो_reg(vpdma, VPDMA_LIST_ADDR, (u32) list->buf.dma_addr);

	ग_लिखो_reg(vpdma, VPDMA_LIST_ATTR,
			(list_num << VPDMA_LIST_NUM_SHFT) |
			(list->type << VPDMA_LIST_TYPE_SHFT) |
			list_size);
	spin_unlock_irqrestore(&vpdma->lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(vpdma_submit_descs);

अटल व्योम dump_dtd(काष्ठा vpdma_dtd *dtd);

व्योम vpdma_update_dma_addr(काष्ठा vpdma_data *vpdma,
	काष्ठा vpdma_desc_list *list, dma_addr_t dma_addr,
	व्योम *ग_लिखो_dtd, पूर्णांक drop, पूर्णांक idx)
अणु
	काष्ठा vpdma_dtd *dtd = list->buf.addr;
	dma_addr_t ग_लिखो_desc_addr;
	पूर्णांक offset;

	dtd += idx;
	vpdma_unmap_desc_buf(vpdma, &list->buf);

	dtd->start_addr = dma_addr;

	/* Calculate ग_लिखो address from the offset of ग_लिखो_dtd from start
	 * of the list->buf
	 */
	offset = (व्योम *)ग_लिखो_dtd - list->buf.addr;
	ग_लिखो_desc_addr = list->buf.dma_addr + offset;

	अगर (drop)
		dtd->desc_ग_लिखो_addr = dtd_desc_ग_लिखो_addr(ग_लिखो_desc_addr,
							   1, 1, 0);
	अन्यथा
		dtd->desc_ग_लिखो_addr = dtd_desc_ग_लिखो_addr(ग_लिखो_desc_addr,
							   1, 0, 0);

	vpdma_map_desc_buf(vpdma, &list->buf);

	dump_dtd(dtd);
पूर्ण
EXPORT_SYMBOL(vpdma_update_dma_addr);

व्योम vpdma_set_max_size(काष्ठा vpdma_data *vpdma, पूर्णांक reg_addr,
			u32 width, u32 height)
अणु
	अगर (reg_addr != VPDMA_MAX_SIZE1 && reg_addr != VPDMA_MAX_SIZE2 &&
	    reg_addr != VPDMA_MAX_SIZE3)
		reg_addr = VPDMA_MAX_SIZE1;

	ग_लिखो_field_reg(vpdma, reg_addr, width - 1,
			VPDMA_MAX_SIZE_WIDTH_MASK, VPDMA_MAX_SIZE_WIDTH_SHFT);

	ग_लिखो_field_reg(vpdma, reg_addr, height - 1,
			VPDMA_MAX_SIZE_HEIGHT_MASK, VPDMA_MAX_SIZE_HEIGHT_SHFT);

पूर्ण
EXPORT_SYMBOL(vpdma_set_max_size);

अटल व्योम dump_cfd(काष्ठा vpdma_cfd *cfd)
अणु
	पूर्णांक class;

	class = cfd_get_class(cfd);

	pr_debug("config descriptor of payload class: %s\n",
		class == CFD_CLS_BLOCK ? "simple block" :
		"address data block");

	अगर (class == CFD_CLS_BLOCK)
		pr_debug("word0: dst_addr_offset = 0x%08x\n",
			cfd->dest_addr_offset);

	अगर (class == CFD_CLS_BLOCK)
		pr_debug("word1: num_data_wrds = %d\n", cfd->block_len);

	pr_debug("word2: payload_addr = 0x%08x\n", cfd->payload_addr);

	pr_debug("word3: pkt_type = %d, direct = %d, class = %d, dest = %d, payload_len = %d\n",
		 cfd_get_pkt_type(cfd),
		 cfd_get_direct(cfd), class, cfd_get_dest(cfd),
		 cfd_get_payload_len(cfd));
पूर्ण

/*
 * append a configuration descriptor to the given descriptor list, where the
 * payload is in the क्रमm of a simple data block specअगरied in the descriptor
 * header, this is used to upload scaler coefficients to the scaler module
 */
व्योम vpdma_add_cfd_block(काष्ठा vpdma_desc_list *list, पूर्णांक client,
		काष्ठा vpdma_buf *blk, u32 dest_offset)
अणु
	काष्ठा vpdma_cfd *cfd;
	पूर्णांक len = blk->size;

	WARN_ON(blk->dma_addr & VPDMA_DESC_ALIGN);

	cfd = list->next;
	WARN_ON((व्योम *)(cfd + 1) > (list->buf.addr + list->buf.size));

	cfd->dest_addr_offset = dest_offset;
	cfd->block_len = len;
	cfd->payload_addr = (u32) blk->dma_addr;
	cfd->ctl_payload_len = cfd_pkt_payload_len(CFD_INसूचीECT, CFD_CLS_BLOCK,
				client, len >> 4);

	list->next = cfd + 1;

	dump_cfd(cfd);
पूर्ण
EXPORT_SYMBOL(vpdma_add_cfd_block);

/*
 * append a configuration descriptor to the given descriptor list, where the
 * payload is in the address data block क्रमmat, this is used to a configure a
 * discontiguous set of MMRs
 */
व्योम vpdma_add_cfd_adb(काष्ठा vpdma_desc_list *list, पूर्णांक client,
		काष्ठा vpdma_buf *adb)
अणु
	काष्ठा vpdma_cfd *cfd;
	अचिन्हित पूर्णांक len = adb->size;

	WARN_ON(len & VPDMA_ADB_SIZE_ALIGN);
	WARN_ON(adb->dma_addr & VPDMA_DESC_ALIGN);

	cfd = list->next;
	BUG_ON((व्योम *)(cfd + 1) > (list->buf.addr + list->buf.size));

	cfd->w0 = 0;
	cfd->w1 = 0;
	cfd->payload_addr = (u32) adb->dma_addr;
	cfd->ctl_payload_len = cfd_pkt_payload_len(CFD_INसूचीECT, CFD_CLS_ADB,
				client, len >> 4);

	list->next = cfd + 1;

	dump_cfd(cfd);
पूर्ण;
EXPORT_SYMBOL(vpdma_add_cfd_adb);

/*
 * control descriptor क्रमmat change based on what type of control descriptor it
 * is, we only use 'sync on channel' control descriptors for now, so assume it's
 * that
 */
अटल व्योम dump_ctd(काष्ठा vpdma_ctd *ctd)
अणु
	pr_debug("control descriptor\n");

	pr_debug("word3: pkt_type = %d, source = %d, ctl_type = %d\n",
		ctd_get_pkt_type(ctd), ctd_get_source(ctd), ctd_get_ctl(ctd));
पूर्ण

/*
 * append a 'sync on channel' type control descriptor to the given descriptor
 * list, this descriptor stalls the VPDMA list till the समय DMA is completed
 * on the specअगरied channel
 */
व्योम vpdma_add_sync_on_channel_ctd(काष्ठा vpdma_desc_list *list,
		क्रमागत vpdma_channel chan)
अणु
	काष्ठा vpdma_ctd *ctd;

	ctd = list->next;
	WARN_ON((व्योम *)(ctd + 1) > (list->buf.addr + list->buf.size));

	ctd->w0 = 0;
	ctd->w1 = 0;
	ctd->w2 = 0;
	ctd->type_source_ctl = ctd_type_source_ctl(chan_info[chan].num,
				CTD_TYPE_SYNC_ON_CHANNEL);

	list->next = ctd + 1;

	dump_ctd(ctd);
पूर्ण
EXPORT_SYMBOL(vpdma_add_sync_on_channel_ctd);

/*
 * append an 'abort_channel' type control descriptor to the given descriptor
 * list, this descriptor पातs any DMA transaction happening using the
 * specअगरied channel
 */
व्योम vpdma_add_पात_channel_ctd(काष्ठा vpdma_desc_list *list,
		पूर्णांक chan_num)
अणु
	काष्ठा vpdma_ctd *ctd;

	ctd = list->next;
	WARN_ON((व्योम *)(ctd + 1) > (list->buf.addr + list->buf.size));

	ctd->w0 = 0;
	ctd->w1 = 0;
	ctd->w2 = 0;
	ctd->type_source_ctl = ctd_type_source_ctl(chan_num,
				CTD_TYPE_ABORT_CHANNEL);

	list->next = ctd + 1;

	dump_ctd(ctd);
पूर्ण
EXPORT_SYMBOL(vpdma_add_पात_channel_ctd);

अटल व्योम dump_dtd(काष्ठा vpdma_dtd *dtd)
अणु
	पूर्णांक dir, chan;

	dir = dtd_get_dir(dtd);
	chan = dtd_get_chan(dtd);

	pr_debug("%s data transfer descriptor for channel %d\n",
		dir == DTD_सूची_OUT ? "outbound" : "inbound", chan);

	pr_debug("word0: data_type = %d, notify = %d, field = %d, 1D = %d, even_ln_skp = %d, odd_ln_skp = %d, line_stride = %d\n",
		dtd_get_data_type(dtd), dtd_get_notअगरy(dtd), dtd_get_field(dtd),
		dtd_get_1d(dtd), dtd_get_even_line_skip(dtd),
		dtd_get_odd_line_skip(dtd), dtd_get_line_stride(dtd));

	अगर (dir == DTD_सूची_IN)
		pr_debug("word1: line_length = %d, xfer_height = %d\n",
			dtd_get_line_length(dtd), dtd_get_xfer_height(dtd));

	pr_debug("word2: start_addr = %x\n", dtd->start_addr);

	pr_debug("word3: pkt_type = %d, mode = %d, dir = %d, chan = %d, pri = %d, next_chan = %d\n",
		 dtd_get_pkt_type(dtd),
		 dtd_get_mode(dtd), dir, chan, dtd_get_priority(dtd),
		 dtd_get_next_chan(dtd));

	अगर (dir == DTD_सूची_IN)
		pr_debug("word4: frame_width = %d, frame_height = %d\n",
			dtd_get_frame_width(dtd), dtd_get_frame_height(dtd));
	अन्यथा
		pr_debug("word4: desc_write_addr = 0x%08x, write_desc = %d, drp_data = %d, use_desc_reg = %d\n",
			dtd_get_desc_ग_लिखो_addr(dtd), dtd_get_ग_लिखो_desc(dtd),
			dtd_get_drop_data(dtd), dtd_get_use_desc(dtd));

	अगर (dir == DTD_सूची_IN)
		pr_debug("word5: hor_start = %d, ver_start = %d\n",
			dtd_get_h_start(dtd), dtd_get_v_start(dtd));
	अन्यथा
		pr_debug("word5: max_width %d, max_height %d\n",
			dtd_get_max_width(dtd), dtd_get_max_height(dtd));

	pr_debug("word6: client specific attr0 = 0x%08x\n", dtd->client_attr0);
	pr_debug("word7: client specific attr1 = 0x%08x\n", dtd->client_attr1);
पूर्ण

/*
 * append an outbound data transfer descriptor to the given descriptor list,
 * this sets up a 'client to memory' VPDMA transfer क्रम the given VPDMA channel
 *
 * @list: vpdma desc list to which we add this descriptor
 * @width: width of the image in pixels in memory
 * @c_rect: compose params of output image
 * @fmt: vpdma data क्रमmat of the buffer
 * dma_addr: dma address as seen by VPDMA
 * max_width: क्रमागत क्रम maximum width of data transfer
 * max_height: क्रमागत क्रम maximum height of data transfer
 * chan: VPDMA channel
 * flags: VPDMA flags to configure some descriptor fields
 */
व्योम vpdma_add_out_dtd(काष्ठा vpdma_desc_list *list, पूर्णांक width,
		पूर्णांक stride, स्थिर काष्ठा v4l2_rect *c_rect,
		स्थिर काष्ठा vpdma_data_क्रमmat *fmt, dma_addr_t dma_addr,
		पूर्णांक max_w, पूर्णांक max_h, क्रमागत vpdma_channel chan, u32 flags)
अणु
	vpdma_rawchan_add_out_dtd(list, width, stride, c_rect, fmt, dma_addr,
				  max_w, max_h, chan_info[chan].num, flags);
पूर्ण
EXPORT_SYMBOL(vpdma_add_out_dtd);

व्योम vpdma_rawchan_add_out_dtd(काष्ठा vpdma_desc_list *list, पूर्णांक width,
		पूर्णांक stride, स्थिर काष्ठा v4l2_rect *c_rect,
		स्थिर काष्ठा vpdma_data_क्रमmat *fmt, dma_addr_t dma_addr,
		पूर्णांक max_w, पूर्णांक max_h, पूर्णांक raw_vpdma_chan, u32 flags)
अणु
	पूर्णांक priority = 0;
	पूर्णांक field = 0;
	पूर्णांक notअगरy = 1;
	पूर्णांक channel, next_chan;
	काष्ठा v4l2_rect rect = *c_rect;
	पूर्णांक depth = fmt->depth;
	काष्ठा vpdma_dtd *dtd;

	channel = next_chan = raw_vpdma_chan;

	अगर (fmt->type == VPDMA_DATA_FMT_TYPE_YUV &&
	    (fmt->data_type == DATA_TYPE_C420 ||
	     fmt->data_type == DATA_TYPE_CB420)) अणु
		rect.height >>= 1;
		rect.top >>= 1;
		depth = 8;
	पूर्ण

	dma_addr += rect.top * stride + (rect.left * depth >> 3);

	dtd = list->next;
	WARN_ON((व्योम *)(dtd + 1) > (list->buf.addr + list->buf.size));

	dtd->type_ctl_stride = dtd_type_ctl_stride(fmt->data_type,
					notअगरy,
					field,
					!!(flags & VPDMA_DATA_FRAME_1D),
					!!(flags & VPDMA_DATA_EVEN_LINE_SKIP),
					!!(flags & VPDMA_DATA_ODD_LINE_SKIP),
					stride);
	dtd->w1 = 0;
	dtd->start_addr = (u32) dma_addr;
	dtd->pkt_ctl = dtd_pkt_ctl(!!(flags & VPDMA_DATA_MODE_TILED),
				DTD_सूची_OUT, channel, priority, next_chan);
	dtd->desc_ग_लिखो_addr = dtd_desc_ग_लिखो_addr(0, 0, 0, 0);
	dtd->max_width_height = dtd_max_width_height(max_w, max_h);
	dtd->client_attr0 = 0;
	dtd->client_attr1 = 0;

	list->next = dtd + 1;

	dump_dtd(dtd);
पूर्ण
EXPORT_SYMBOL(vpdma_rawchan_add_out_dtd);

/*
 * append an inbound data transfer descriptor to the given descriptor list,
 * this sets up a 'memory to client' VPDMA transfer क्रम the given VPDMA channel
 *
 * @list: vpdma desc list to which we add this descriptor
 * @width: width of the image in pixels in memory(not the cropped width)
 * @c_rect: crop params of input image
 * @fmt: vpdma data क्रमmat of the buffer
 * dma_addr: dma address as seen by VPDMA
 * chan: VPDMA channel
 * field: top or bottom field info of the input image
 * flags: VPDMA flags to configure some descriptor fields
 * frame_width/height: the complete width/height of the image presented to the
 *			client (this makes sense when multiple channels are
 *			connected to the same client, क्रमming a larger frame)
 * start_h, start_v: position where the given channel starts providing pixel
 *			data to the client (makes sense when multiple channels
 *			contribute to the client)
 */
व्योम vpdma_add_in_dtd(काष्ठा vpdma_desc_list *list, पूर्णांक width,
		पूर्णांक stride, स्थिर काष्ठा v4l2_rect *c_rect,
		स्थिर काष्ठा vpdma_data_क्रमmat *fmt, dma_addr_t dma_addr,
		क्रमागत vpdma_channel chan, पूर्णांक field, u32 flags, पूर्णांक frame_width,
		पूर्णांक frame_height, पूर्णांक start_h, पूर्णांक start_v)
अणु
	पूर्णांक priority = 0;
	पूर्णांक notअगरy = 1;
	पूर्णांक depth = fmt->depth;
	पूर्णांक channel, next_chan;
	काष्ठा v4l2_rect rect = *c_rect;
	काष्ठा vpdma_dtd *dtd;

	channel = next_chan = chan_info[chan].num;

	अगर (fmt->type == VPDMA_DATA_FMT_TYPE_YUV &&
	    (fmt->data_type == DATA_TYPE_C420 ||
	     fmt->data_type == DATA_TYPE_CB420)) अणु
		rect.height >>= 1;
		rect.top >>= 1;
		depth = 8;
	पूर्ण

	dma_addr += rect.top * stride + (rect.left * depth >> 3);

	dtd = list->next;
	WARN_ON((व्योम *)(dtd + 1) > (list->buf.addr + list->buf.size));

	dtd->type_ctl_stride = dtd_type_ctl_stride(fmt->data_type,
					notअगरy,
					field,
					!!(flags & VPDMA_DATA_FRAME_1D),
					!!(flags & VPDMA_DATA_EVEN_LINE_SKIP),
					!!(flags & VPDMA_DATA_ODD_LINE_SKIP),
					stride);

	dtd->xfer_length_height = dtd_xfer_length_height(rect.width,
					rect.height);
	dtd->start_addr = (u32) dma_addr;
	dtd->pkt_ctl = dtd_pkt_ctl(!!(flags & VPDMA_DATA_MODE_TILED),
				DTD_सूची_IN, channel, priority, next_chan);
	dtd->frame_width_height = dtd_frame_width_height(frame_width,
					frame_height);
	dtd->start_h_v = dtd_start_h_v(start_h, start_v);
	dtd->client_attr0 = 0;
	dtd->client_attr1 = 0;

	list->next = dtd + 1;

	dump_dtd(dtd);
पूर्ण
EXPORT_SYMBOL(vpdma_add_in_dtd);

पूर्णांक vpdma_hwlist_alloc(काष्ठा vpdma_data *vpdma, व्योम *priv)
अणु
	पूर्णांक i, list_num = -1;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vpdma->lock, flags);
	क्रम (i = 0; i < VPDMA_MAX_NUM_LIST && vpdma->hwlist_used[i]; i++)
		;

	अगर (i < VPDMA_MAX_NUM_LIST) अणु
		list_num = i;
		vpdma->hwlist_used[i] = true;
		vpdma->hwlist_priv[i] = priv;
	पूर्ण
	spin_unlock_irqrestore(&vpdma->lock, flags);

	वापस list_num;
पूर्ण
EXPORT_SYMBOL(vpdma_hwlist_alloc);

व्योम *vpdma_hwlist_get_priv(काष्ठा vpdma_data *vpdma, पूर्णांक list_num)
अणु
	अगर (!vpdma || list_num >= VPDMA_MAX_NUM_LIST)
		वापस शून्य;

	वापस vpdma->hwlist_priv[list_num];
पूर्ण
EXPORT_SYMBOL(vpdma_hwlist_get_priv);

व्योम *vpdma_hwlist_release(काष्ठा vpdma_data *vpdma, पूर्णांक list_num)
अणु
	व्योम *priv;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vpdma->lock, flags);
	vpdma->hwlist_used[list_num] = false;
	priv = vpdma->hwlist_priv;
	spin_unlock_irqrestore(&vpdma->lock, flags);

	वापस priv;
पूर्ण
EXPORT_SYMBOL(vpdma_hwlist_release);

/* set or clear the mask क्रम list complete पूर्णांकerrupt */
व्योम vpdma_enable_list_complete_irq(काष्ठा vpdma_data *vpdma, पूर्णांक irq_num,
		पूर्णांक list_num, bool enable)
अणु
	u32 reg_addr = VPDMA_INT_LIST0_MASK + VPDMA_INTX_OFFSET * irq_num;
	u32 val;

	val = पढ़ो_reg(vpdma, reg_addr);
	अगर (enable)
		val |= (1 << (list_num * 2));
	अन्यथा
		val &= ~(1 << (list_num * 2));
	ग_लिखो_reg(vpdma, reg_addr, val);
पूर्ण
EXPORT_SYMBOL(vpdma_enable_list_complete_irq);

/* get the LIST_STAT रेजिस्टर */
अचिन्हित पूर्णांक vpdma_get_list_stat(काष्ठा vpdma_data *vpdma, पूर्णांक irq_num)
अणु
	u32 reg_addr = VPDMA_INT_LIST0_STAT + VPDMA_INTX_OFFSET * irq_num;

	वापस पढ़ो_reg(vpdma, reg_addr);
पूर्ण
EXPORT_SYMBOL(vpdma_get_list_stat);

/* get the LIST_MASK रेजिस्टर */
अचिन्हित पूर्णांक vpdma_get_list_mask(काष्ठा vpdma_data *vpdma, पूर्णांक irq_num)
अणु
	u32 reg_addr = VPDMA_INT_LIST0_MASK + VPDMA_INTX_OFFSET * irq_num;

	वापस पढ़ो_reg(vpdma, reg_addr);
पूर्ण
EXPORT_SYMBOL(vpdma_get_list_mask);

/* clear previously occurred list पूर्णांकerrupts in the LIST_STAT रेजिस्टर */
व्योम vpdma_clear_list_stat(काष्ठा vpdma_data *vpdma, पूर्णांक irq_num,
			   पूर्णांक list_num)
अणु
	u32 reg_addr = VPDMA_INT_LIST0_STAT + VPDMA_INTX_OFFSET * irq_num;

	ग_लिखो_reg(vpdma, reg_addr, 3 << (list_num * 2));
पूर्ण
EXPORT_SYMBOL(vpdma_clear_list_stat);

व्योम vpdma_set_bg_color(काष्ठा vpdma_data *vpdma,
		काष्ठा vpdma_data_क्रमmat *fmt, u32 color)
अणु
	अगर (fmt->type == VPDMA_DATA_FMT_TYPE_RGB)
		ग_लिखो_reg(vpdma, VPDMA_BG_RGB, color);
	अन्यथा अगर (fmt->type == VPDMA_DATA_FMT_TYPE_YUV)
		ग_लिखो_reg(vpdma, VPDMA_BG_YUV, color);
पूर्ण
EXPORT_SYMBOL(vpdma_set_bg_color);

/*
 * configures the output mode of the line buffer क्रम the given client, the
 * line buffer content can either be mirrored(each line repeated twice) or
 * passed to the client as is
 */
व्योम vpdma_set_line_mode(काष्ठा vpdma_data *vpdma, पूर्णांक line_mode,
		क्रमागत vpdma_channel chan)
अणु
	पूर्णांक client_cstat = chan_info[chan].cstat_offset;

	ग_लिखो_field_reg(vpdma, client_cstat, line_mode,
		VPDMA_CSTAT_LINE_MODE_MASK, VPDMA_CSTAT_LINE_MODE_SHIFT);
पूर्ण
EXPORT_SYMBOL(vpdma_set_line_mode);

/*
 * configures the event which should trigger VPDMA transfer क्रम the given
 * client
 */
व्योम vpdma_set_frame_start_event(काष्ठा vpdma_data *vpdma,
		क्रमागत vpdma_frame_start_event fs_event,
		क्रमागत vpdma_channel chan)
अणु
	पूर्णांक client_cstat = chan_info[chan].cstat_offset;

	ग_लिखो_field_reg(vpdma, client_cstat, fs_event,
		VPDMA_CSTAT_FRAME_START_MASK, VPDMA_CSTAT_FRAME_START_SHIFT);
पूर्ण
EXPORT_SYMBOL(vpdma_set_frame_start_event);

अटल व्योम vpdma_firmware_cb(स्थिर काष्ठा firmware *f, व्योम *context)
अणु
	काष्ठा vpdma_data *vpdma = context;
	काष्ठा vpdma_buf fw_dma_buf;
	पूर्णांक i, r;

	dev_dbg(&vpdma->pdev->dev, "firmware callback\n");

	अगर (!f || !f->data) अणु
		dev_err(&vpdma->pdev->dev, "couldn't get firmware\n");
		वापस;
	पूर्ण

	/* alपढ़ोy initialized */
	अगर (पढ़ो_field_reg(vpdma, VPDMA_LIST_ATTR, VPDMA_LIST_RDY_MASK,
			VPDMA_LIST_RDY_SHFT)) अणु
		vpdma->cb(vpdma->pdev);
		वापस;
	पूर्ण

	r = vpdma_alloc_desc_buf(&fw_dma_buf, f->size);
	अगर (r) अणु
		dev_err(&vpdma->pdev->dev,
			"failed to allocate dma buffer for firmware\n");
		जाओ rel_fw;
	पूर्ण

	स_नकल(fw_dma_buf.addr, f->data, f->size);

	vpdma_map_desc_buf(vpdma, &fw_dma_buf);

	ग_लिखो_reg(vpdma, VPDMA_LIST_ADDR, (u32) fw_dma_buf.dma_addr);

	क्रम (i = 0; i < 100; i++) अणु		/* max 1 second */
		msleep_पूर्णांकerruptible(10);

		अगर (पढ़ो_field_reg(vpdma, VPDMA_LIST_ATTR, VPDMA_LIST_RDY_MASK,
				VPDMA_LIST_RDY_SHFT))
			अवरोध;
	पूर्ण

	अगर (i == 100) अणु
		dev_err(&vpdma->pdev->dev, "firmware upload failed\n");
		जाओ मुक्त_buf;
	पूर्ण

	vpdma->cb(vpdma->pdev);

मुक्त_buf:
	vpdma_unmap_desc_buf(vpdma, &fw_dma_buf);

	vpdma_मुक्त_desc_buf(&fw_dma_buf);
rel_fw:
	release_firmware(f);
पूर्ण

अटल पूर्णांक vpdma_load_firmware(काष्ठा vpdma_data *vpdma)
अणु
	पूर्णांक r;
	काष्ठा device *dev = &vpdma->pdev->dev;

	r = request_firmware_noरुको(THIS_MODULE, 1,
		(स्थिर अक्षर *) VPDMA_FIRMWARE, dev, GFP_KERNEL, vpdma,
		vpdma_firmware_cb);
	अगर (r) अणु
		dev_err(dev, "firmware not available %s\n", VPDMA_FIRMWARE);
		वापस r;
	पूर्ण अन्यथा अणु
		dev_info(dev, "loading firmware %s\n", VPDMA_FIRMWARE);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक vpdma_create(काष्ठा platक्रमm_device *pdev, काष्ठा vpdma_data *vpdma,
		व्योम (*cb)(काष्ठा platक्रमm_device *pdev))
अणु
	काष्ठा resource *res;
	पूर्णांक r;

	dev_dbg(&pdev->dev, "vpdma_create\n");

	vpdma->pdev = pdev;
	vpdma->cb = cb;
	spin_lock_init(&vpdma->lock);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "vpdma");
	अगर (res == शून्य) अणु
		dev_err(&pdev->dev, "missing platform resources data\n");
		वापस -ENODEV;
	पूर्ण

	vpdma->base = devm_ioremap(&pdev->dev, res->start, resource_size(res));
	अगर (!vpdma->base) अणु
		dev_err(&pdev->dev, "failed to ioremap\n");
		वापस -ENOMEM;
	पूर्ण

	r = vpdma_load_firmware(vpdma);
	अगर (r) अणु
		pr_err("failed to load firmware %s\n", VPDMA_FIRMWARE);
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(vpdma_create);

MODULE_AUTHOR("Texas Instruments Inc.");
MODULE_FIRMWARE(VPDMA_FIRMWARE);
MODULE_LICENSE("GPL v2");

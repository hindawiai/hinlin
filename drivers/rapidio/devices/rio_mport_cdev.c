<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * RapidIO mport अक्षरacter device
 *
 * Copyright 2014-2015 Integrated Device Technology, Inc.
 *    Alexandre Bounine <alexandre.bounine@idt.com>
 * Copyright 2014-2015 Prodrive Technologies
 *    Andre van Herk <andre.van.herk@prodrive-technologies.com>
 *    Jerry Jacobs <jerry.jacobs@prodrive-technologies.com>
 * Copyright (C) 2014 Texas Instruments Incorporated
 *    Aurelien Jacquiot <a-jacquiot@ti.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/cdev.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/list.h>
#समावेश <linux/fs.h>
#समावेश <linux/err.h>
#समावेश <linux/net.h>
#समावेश <linux/poll.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sched.h>
#समावेश <linux/kfअगरo.h>

#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mman.h>

#समावेश <linux/dma-mapping.h>
#अगर_घोषित CONFIG_RAPIDIO_DMA_ENGINE
#समावेश <linux/dmaengine.h>
#पूर्ण_अगर

#समावेश <linux/rपन.स>
#समावेश <linux/rio_ids.h>
#समावेश <linux/rio_drv.h>
#समावेश <linux/rio_mport_cdev.h>

#समावेश "../rio.h"

#घोषणा DRV_NAME	"rio_mport"
#घोषणा DRV_PREFIX	DRV_NAME ": "
#घोषणा DEV_NAME	"rio_mport"
#घोषणा DRV_VERSION     "1.0.0"

/* Debug output filtering masks */
क्रमागत अणु
	DBG_NONE	= 0,
	DBG_INIT	= BIT(0), /* driver init */
	DBG_EXIT	= BIT(1), /* driver निकास */
	DBG_MPORT	= BIT(2), /* mport add/हटाओ */
	DBG_RDEV	= BIT(3), /* RapidIO device add/हटाओ */
	DBG_DMA		= BIT(4), /* DMA transfer messages */
	DBG_MMAP	= BIT(5), /* mapping messages */
	DBG_IBW		= BIT(6), /* inbound winकरोw */
	DBG_EVENT	= BIT(7), /* event handling messages */
	DBG_OBW		= BIT(8), /* outbound winकरोw messages */
	DBG_DBELL	= BIT(9), /* करोorbell messages */
	DBG_ALL		= ~0,
पूर्ण;

#अगर_घोषित DEBUG
#घोषणा rmcd_debug(level, fmt, arg...)		\
	करो अणु					\
		अगर (DBG_##level & dbg_level)	\
			pr_debug(DRV_PREFIX "%s: " fmt "\n", __func__, ##arg); \
	पूर्ण जबतक (0)
#अन्यथा
#घोषणा rmcd_debug(level, fmt, arg...) \
		no_prपूर्णांकk(KERN_DEBUG pr_fmt(DRV_PREFIX fmt "\n"), ##arg)
#पूर्ण_अगर

#घोषणा rmcd_warn(fmt, arg...) \
	pr_warn(DRV_PREFIX "%s WARNING " fmt "\n", __func__, ##arg)

#घोषणा rmcd_error(fmt, arg...) \
	pr_err(DRV_PREFIX "%s ERROR " fmt "\n", __func__, ##arg)

MODULE_AUTHOR("Jerry Jacobs <jerry.jacobs@prodrive-technologies.com>");
MODULE_AUTHOR("Aurelien Jacquiot <a-jacquiot@ti.com>");
MODULE_AUTHOR("Alexandre Bounine <alexandre.bounine@idt.com>");
MODULE_AUTHOR("Andre van Herk <andre.van.herk@prodrive-technologies.com>");
MODULE_DESCRIPTION("RapidIO mport character device driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);

अटल पूर्णांक dma_समयout = 3000; /* DMA transfer समयout in msec */
module_param(dma_समयout, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(dma_समयout, "DMA Transfer Timeout in msec (default: 3000)");

#अगर_घोषित DEBUG
अटल u32 dbg_level = DBG_NONE;
module_param(dbg_level, uपूर्णांक, S_IWUSR | S_IWGRP | S_IRUGO);
MODULE_PARM_DESC(dbg_level, "Debugging output level (default 0 = none)");
#पूर्ण_अगर

/*
 * An पूर्णांकernal DMA coherent buffer
 */
काष्ठा mport_dma_buf अणु
	व्योम		*ib_base;
	dma_addr_t	ib_phys;
	u32		ib_size;
	u64		ib_rio_base;
	bool		ib_map;
	काष्ठा file	*filp;
पूर्ण;

/*
 * Internal memory mapping काष्ठाure
 */
क्रमागत rio_mport_map_dir अणु
	MAP_INBOUND,
	MAP_OUTBOUND,
	MAP_DMA,
पूर्ण;

काष्ठा rio_mport_mapping अणु
	काष्ठा list_head node;
	काष्ठा mport_dev *md;
	क्रमागत rio_mport_map_dir dir;
	u16 rioid;
	u64 rio_addr;
	dma_addr_t phys_addr; /* क्रम mmap */
	व्योम *virt_addr; /* kernel address, क्रम dma_मुक्त_coherent */
	u64 size;
	काष्ठा kref ref; /* refcount of vmas sharing the mapping */
	काष्ठा file *filp;
पूर्ण;

काष्ठा rio_mport_dma_map अणु
	पूर्णांक valid;
	u64 length;
	व्योम *vaddr;
	dma_addr_t paddr;
पूर्ण;

#घोषणा MPORT_MAX_DMA_BUFS	16
#घोषणा MPORT_EVENT_DEPTH	10

/*
 * mport_dev  driver-specअगरic काष्ठाure that represents mport device
 * @active    mport device status flag
 * @node      list node to मुख्यtain list of रेजिस्टरed mports
 * @cdev      अक्षरacter device
 * @dev       associated device object
 * @mport     associated subप्रणाली's master port device object
 * @buf_mutex lock क्रम buffer handling
 * @file_mutex - lock क्रम खोलो files list
 * @file_list  - list of खोलो files on given mport
 * @properties properties of this mport
 * @portग_लिखोs queue of inbound portग_लिखोs
 * @pw_lock    lock क्रम port ग_लिखो queue
 * @mappings   queue क्रम memory mappings
 * @dma_chan   DMA channels associated with this device
 * @dma_ref:
 * @comp:
 */
काष्ठा mport_dev अणु
	atomic_t		active;
	काष्ठा list_head	node;
	काष्ठा cdev		cdev;
	काष्ठा device		dev;
	काष्ठा rio_mport	*mport;
	काष्ठा mutex		buf_mutex;
	काष्ठा mutex		file_mutex;
	काष्ठा list_head	file_list;
	काष्ठा rio_mport_properties	properties;
	काष्ठा list_head		करोorbells;
	spinlock_t			db_lock;
	काष्ठा list_head		portग_लिखोs;
	spinlock_t			pw_lock;
	काष्ठा list_head	mappings;
#अगर_घोषित CONFIG_RAPIDIO_DMA_ENGINE
	काष्ठा dma_chan *dma_chan;
	काष्ठा kref	dma_ref;
	काष्ठा completion comp;
#पूर्ण_अगर
पूर्ण;

/*
 * mport_cdev_priv - data काष्ठाure specअगरic to inभागidual file object
 *                   associated with an खोलो device
 * @md    master port अक्षरacter device object
 * @async_queue - asynchronous notअगरication queue
 * @list - file objects tracking list
 * @db_filters    inbound करोorbell filters क्रम this descriptor
 * @pw_filters    portग_लिखो filters क्रम this descriptor
 * @event_fअगरo    event fअगरo क्रम this descriptor
 * @event_rx_रुको रुको queue क्रम this descriptor
 * @fअगरo_lock     lock क्रम event_fअगरo
 * @event_mask    event mask क्रम this descriptor
 * @dmach DMA engine channel allocated क्रम specअगरic file object
 */
काष्ठा mport_cdev_priv अणु
	काष्ठा mport_dev	*md;
	काष्ठा fasync_काष्ठा	*async_queue;
	काष्ठा list_head	list;
	काष्ठा list_head	db_filters;
	काष्ठा list_head        pw_filters;
	काष्ठा kfअगरo            event_fअगरo;
	रुको_queue_head_t       event_rx_रुको;
	spinlock_t              fअगरo_lock;
	u32			event_mask; /* RIO_DOORBELL, RIO_PORTWRITE */
#अगर_घोषित CONFIG_RAPIDIO_DMA_ENGINE
	काष्ठा dma_chan		*dmach;
	काष्ठा list_head	async_list;
	spinlock_t              req_lock;
	काष्ठा mutex		dma_lock;
	काष्ठा kref		dma_ref;
	काष्ठा completion	comp;
#पूर्ण_अगर
पूर्ण;

/*
 * rio_mport_pw_filter - काष्ठाure to describe a portग_लिखो filter
 * md_node   node in mport device's list
 * priv_node node in निजी file object's list
 * priv      reference to निजी data
 * filter    actual portग_लिखो filter
 */
काष्ठा rio_mport_pw_filter अणु
	काष्ठा list_head md_node;
	काष्ठा list_head priv_node;
	काष्ठा mport_cdev_priv *priv;
	काष्ठा rio_pw_filter filter;
पूर्ण;

/*
 * rio_mport_db_filter - काष्ठाure to describe a करोorbell filter
 * @data_node reference to device node
 * @priv_node node in निजी data
 * @priv      reference to निजी data
 * @filter    actual करोorbell filter
 */
काष्ठा rio_mport_db_filter अणु
	काष्ठा list_head data_node;
	काष्ठा list_head priv_node;
	काष्ठा mport_cdev_priv *priv;
	काष्ठा rio_करोorbell_filter filter;
पूर्ण;

अटल LIST_HEAD(mport_devs);
अटल DEFINE_MUTEX(mport_devs_lock);

#अगर (0) /* used by commented out portion of poll function : FIXME */
अटल DECLARE_WAIT_QUEUE_HEAD(mport_cdev_रुको);
#पूर्ण_अगर

अटल काष्ठा class *dev_class;
अटल dev_t dev_number;

अटल व्योम mport_release_mapping(काष्ठा kref *ref);

अटल पूर्णांक rio_mport_मुख्यt_rd(काष्ठा mport_cdev_priv *priv, व्योम __user *arg,
			      पूर्णांक local)
अणु
	काष्ठा rio_mport *mport = priv->md->mport;
	काष्ठा rio_mport_मुख्यt_io मुख्यt_io;
	u32 *buffer;
	u32 offset;
	माप_प्रकार length;
	पूर्णांक ret, i;

	अगर (unlikely(copy_from_user(&मुख्यt_io, arg, माप(मुख्यt_io))))
		वापस -EFAULT;

	अगर ((मुख्यt_io.offset % 4) ||
	    (मुख्यt_io.length == 0) || (मुख्यt_io.length % 4) ||
	    (मुख्यt_io.length + मुख्यt_io.offset) > RIO_MAINT_SPACE_SZ)
		वापस -EINVAL;

	buffer = vदो_स्मृति(मुख्यt_io.length);
	अगर (buffer == शून्य)
		वापस -ENOMEM;
	length = मुख्यt_io.length/माप(u32);
	offset = मुख्यt_io.offset;

	क्रम (i = 0; i < length; i++) अणु
		अगर (local)
			ret = __rio_local_पढ़ो_config_32(mport,
				offset, &buffer[i]);
		अन्यथा
			ret = rio_mport_पढ़ो_config_32(mport, मुख्यt_io.rioid,
				मुख्यt_पन.सopcount, offset, &buffer[i]);
		अगर (ret)
			जाओ out;

		offset += 4;
	पूर्ण

	अगर (unlikely(copy_to_user((व्योम __user *)(uपूर्णांकptr_t)मुख्यt_io.buffer,
				   buffer, मुख्यt_io.length)))
		ret = -EFAULT;
out:
	vमुक्त(buffer);
	वापस ret;
पूर्ण

अटल पूर्णांक rio_mport_मुख्यt_wr(काष्ठा mport_cdev_priv *priv, व्योम __user *arg,
			      पूर्णांक local)
अणु
	काष्ठा rio_mport *mport = priv->md->mport;
	काष्ठा rio_mport_मुख्यt_io मुख्यt_io;
	u32 *buffer;
	u32 offset;
	माप_प्रकार length;
	पूर्णांक ret = -EINVAL, i;

	अगर (unlikely(copy_from_user(&मुख्यt_io, arg, माप(मुख्यt_io))))
		वापस -EFAULT;

	अगर ((मुख्यt_io.offset % 4) ||
	    (मुख्यt_io.length == 0) || (मुख्यt_io.length % 4) ||
	    (मुख्यt_io.length + मुख्यt_io.offset) > RIO_MAINT_SPACE_SZ)
		वापस -EINVAL;

	buffer = vदो_स्मृति(मुख्यt_io.length);
	अगर (buffer == शून्य)
		वापस -ENOMEM;
	length = मुख्यt_io.length;

	अगर (unlikely(copy_from_user(buffer,
			(व्योम __user *)(uपूर्णांकptr_t)मुख्यt_io.buffer, length))) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	offset = मुख्यt_io.offset;
	length /= माप(u32);

	क्रम (i = 0; i < length; i++) अणु
		अगर (local)
			ret = __rio_local_ग_लिखो_config_32(mport,
							  offset, buffer[i]);
		अन्यथा
			ret = rio_mport_ग_लिखो_config_32(mport, मुख्यt_io.rioid,
							मुख्यt_पन.सopcount,
							offset, buffer[i]);
		अगर (ret)
			जाओ out;

		offset += 4;
	पूर्ण

out:
	vमुक्त(buffer);
	वापस ret;
पूर्ण


/*
 * Inbound/outbound memory mapping functions
 */
अटल पूर्णांक
rio_mport_create_outbound_mapping(काष्ठा mport_dev *md, काष्ठा file *filp,
				  u16 rioid, u64 raddr, u32 size,
				  dma_addr_t *paddr)
अणु
	काष्ठा rio_mport *mport = md->mport;
	काष्ठा rio_mport_mapping *map;
	पूर्णांक ret;

	rmcd_debug(OBW, "did=%d ra=0x%llx sz=0x%x", rioid, raddr, size);

	map = kzalloc(माप(*map), GFP_KERNEL);
	अगर (map == शून्य)
		वापस -ENOMEM;

	ret = rio_map_outb_region(mport, rioid, raddr, size, 0, paddr);
	अगर (ret < 0)
		जाओ err_map_outb;

	map->dir = MAP_OUTBOUND;
	map->rioid = rioid;
	map->rio_addr = raddr;
	map->size = size;
	map->phys_addr = *paddr;
	map->filp = filp;
	map->md = md;
	kref_init(&map->ref);
	list_add_tail(&map->node, &md->mappings);
	वापस 0;
err_map_outb:
	kमुक्त(map);
	वापस ret;
पूर्ण

अटल पूर्णांक
rio_mport_get_outbound_mapping(काष्ठा mport_dev *md, काष्ठा file *filp,
			       u16 rioid, u64 raddr, u32 size,
			       dma_addr_t *paddr)
अणु
	काष्ठा rio_mport_mapping *map;
	पूर्णांक err = -ENOMEM;

	mutex_lock(&md->buf_mutex);
	list_क्रम_each_entry(map, &md->mappings, node) अणु
		अगर (map->dir != MAP_OUTBOUND)
			जारी;
		अगर (rioid == map->rioid &&
		    raddr == map->rio_addr && size == map->size) अणु
			*paddr = map->phys_addr;
			err = 0;
			अवरोध;
		पूर्ण अन्यथा अगर (rioid == map->rioid &&
			   raddr < (map->rio_addr + map->size - 1) &&
			   (raddr + size) > map->rio_addr) अणु
			err = -EBUSY;
			अवरोध;
		पूर्ण
	पूर्ण

	/* If not found, create new */
	अगर (err == -ENOMEM)
		err = rio_mport_create_outbound_mapping(md, filp, rioid, raddr,
						size, paddr);
	mutex_unlock(&md->buf_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक rio_mport_obw_map(काष्ठा file *filp, व्योम __user *arg)
अणु
	काष्ठा mport_cdev_priv *priv = filp->निजी_data;
	काष्ठा mport_dev *data = priv->md;
	काष्ठा rio_mmap map;
	dma_addr_t paddr;
	पूर्णांक ret;

	अगर (unlikely(copy_from_user(&map, arg, माप(map))))
		वापस -EFAULT;

	rmcd_debug(OBW, "did=%d ra=0x%llx sz=0x%llx",
		   map.rioid, map.rio_addr, map.length);

	ret = rio_mport_get_outbound_mapping(data, filp, map.rioid,
					     map.rio_addr, map.length, &paddr);
	अगर (ret < 0) अणु
		rmcd_error("Failed to set OBW err= %d", ret);
		वापस ret;
	पूर्ण

	map.handle = paddr;

	अगर (unlikely(copy_to_user(arg, &map, माप(map))))
		वापस -EFAULT;
	वापस 0;
पूर्ण

/*
 * rio_mport_obw_मुक्त() - unmap an OutBound Winकरोw from RapidIO address space
 *
 * @priv: driver निजी data
 * @arg:  buffer handle वापसed by allocation routine
 */
अटल पूर्णांक rio_mport_obw_मुक्त(काष्ठा file *filp, व्योम __user *arg)
अणु
	काष्ठा mport_cdev_priv *priv = filp->निजी_data;
	काष्ठा mport_dev *md = priv->md;
	u64 handle;
	काष्ठा rio_mport_mapping *map, *_map;

	अगर (!md->mport->ops->unmap_outb)
		वापस -EPROTONOSUPPORT;

	अगर (copy_from_user(&handle, arg, माप(handle)))
		वापस -EFAULT;

	rmcd_debug(OBW, "h=0x%llx", handle);

	mutex_lock(&md->buf_mutex);
	list_क्रम_each_entry_safe(map, _map, &md->mappings, node) अणु
		अगर (map->dir == MAP_OUTBOUND && map->phys_addr == handle) अणु
			अगर (map->filp == filp) अणु
				rmcd_debug(OBW, "kref_put h=0x%llx", handle);
				map->filp = शून्य;
				kref_put(&map->ref, mport_release_mapping);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&md->buf_mutex);

	वापस 0;
पूर्ण

/*
 * मुख्यt_hdid_set() - Set the host Device ID
 * @priv: driver निजी data
 * @arg:	Device Id
 */
अटल पूर्णांक मुख्यt_hdid_set(काष्ठा mport_cdev_priv *priv, व्योम __user *arg)
अणु
	काष्ठा mport_dev *md = priv->md;
	u16 hdid;

	अगर (copy_from_user(&hdid, arg, माप(hdid)))
		वापस -EFAULT;

	md->mport->host_deviceid = hdid;
	md->properties.hdid = hdid;
	rio_local_set_device_id(md->mport, hdid);

	rmcd_debug(MPORT, "Set host device Id to %d", hdid);

	वापस 0;
पूर्ण

/*
 * मुख्यt_comptag_set() - Set the host Component Tag
 * @priv: driver निजी data
 * @arg:	Component Tag
 */
अटल पूर्णांक मुख्यt_comptag_set(काष्ठा mport_cdev_priv *priv, व्योम __user *arg)
अणु
	काष्ठा mport_dev *md = priv->md;
	u32 comptag;

	अगर (copy_from_user(&comptag, arg, माप(comptag)))
		वापस -EFAULT;

	rio_local_ग_लिखो_config_32(md->mport, RIO_COMPONENT_TAG_CSR, comptag);

	rmcd_debug(MPORT, "Set host Component Tag to %d", comptag);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_RAPIDIO_DMA_ENGINE

काष्ठा mport_dma_req अणु
	काष्ठा kref refcount;
	काष्ठा list_head node;
	काष्ठा file *filp;
	काष्ठा mport_cdev_priv *priv;
	क्रमागत rio_transfer_sync sync;
	काष्ठा sg_table sgt;
	काष्ठा page **page_list;
	अचिन्हित पूर्णांक nr_pages;
	काष्ठा rio_mport_mapping *map;
	काष्ठा dma_chan *dmach;
	क्रमागत dma_data_direction dir;
	dma_cookie_t cookie;
	क्रमागत dma_status	status;
	काष्ठा completion req_comp;
पूर्ण;

अटल व्योम mport_release_def_dma(काष्ठा kref *dma_ref)
अणु
	काष्ठा mport_dev *md =
			container_of(dma_ref, काष्ठा mport_dev, dma_ref);

	rmcd_debug(EXIT, "DMA_%d", md->dma_chan->chan_id);
	rio_release_dma(md->dma_chan);
	md->dma_chan = शून्य;
पूर्ण

अटल व्योम mport_release_dma(काष्ठा kref *dma_ref)
अणु
	काष्ठा mport_cdev_priv *priv =
			container_of(dma_ref, काष्ठा mport_cdev_priv, dma_ref);

	rmcd_debug(EXIT, "DMA_%d", priv->dmach->chan_id);
	complete(&priv->comp);
पूर्ण

अटल व्योम dma_req_मुक्त(काष्ठा kref *ref)
अणु
	काष्ठा mport_dma_req *req = container_of(ref, काष्ठा mport_dma_req,
			refcount);
	काष्ठा mport_cdev_priv *priv = req->priv;

	dma_unmap_sg(req->dmach->device->dev,
		     req->sgt.sgl, req->sgt.nents, req->dir);
	sg_मुक्त_table(&req->sgt);
	अगर (req->page_list) अणु
		unpin_user_pages(req->page_list, req->nr_pages);
		kमुक्त(req->page_list);
	पूर्ण

	अगर (req->map) अणु
		mutex_lock(&req->map->md->buf_mutex);
		kref_put(&req->map->ref, mport_release_mapping);
		mutex_unlock(&req->map->md->buf_mutex);
	पूर्ण

	kref_put(&priv->dma_ref, mport_release_dma);

	kमुक्त(req);
पूर्ण

अटल व्योम dma_xfer_callback(व्योम *param)
अणु
	काष्ठा mport_dma_req *req = (काष्ठा mport_dma_req *)param;
	काष्ठा mport_cdev_priv *priv = req->priv;

	req->status = dma_async_is_tx_complete(priv->dmach, req->cookie,
					       शून्य, शून्य);
	complete(&req->req_comp);
	kref_put(&req->refcount, dma_req_मुक्त);
पूर्ण

/*
 * prep_dma_xfer() - Configure and send request to DMAengine to prepare DMA
 *                   transfer object.
 * Returns poपूर्णांकer to DMA transaction descriptor allocated by DMA driver on
 * success or ERR_PTR (and/or शून्य) अगर failed. Caller must check वापसed
 * non-शून्य poपूर्णांकer using IS_ERR macro.
 */
अटल काष्ठा dma_async_tx_descriptor
*prep_dma_xfer(काष्ठा dma_chan *chan, काष्ठा rio_transfer_io *transfer,
	काष्ठा sg_table *sgt, पूर्णांक nents, क्रमागत dma_transfer_direction dir,
	क्रमागत dma_ctrl_flags flags)
अणु
	काष्ठा rio_dma_data tx_data;

	tx_data.sg = sgt->sgl;
	tx_data.sg_len = nents;
	tx_data.rio_addr_u = 0;
	tx_data.rio_addr = transfer->rio_addr;
	अगर (dir == DMA_MEM_TO_DEV) अणु
		चयन (transfer->method) अणु
		हाल RIO_EXCHANGE_NWRITE:
			tx_data.wr_type = RDW_ALL_NWRITE;
			अवरोध;
		हाल RIO_EXCHANGE_NWRITE_R_ALL:
			tx_data.wr_type = RDW_ALL_NWRITE_R;
			अवरोध;
		हाल RIO_EXCHANGE_NWRITE_R:
			tx_data.wr_type = RDW_LAST_NWRITE_R;
			अवरोध;
		हाल RIO_EXCHANGE_DEFAULT:
			tx_data.wr_type = RDW_DEFAULT;
			अवरोध;
		शेष:
			वापस ERR_PTR(-EINVAL);
		पूर्ण
	पूर्ण

	वापस rio_dma_prep_xfer(chan, transfer->rioid, &tx_data, dir, flags);
पूर्ण

/* Request DMA channel associated with this mport device.
 * Try to request DMA channel क्रम every new process that खोलोed given
 * mport. If a new DMA channel is not available use शेष channel
 * which is the first DMA channel खोलोed on mport device.
 */
अटल पूर्णांक get_dma_channel(काष्ठा mport_cdev_priv *priv)
अणु
	mutex_lock(&priv->dma_lock);
	अगर (!priv->dmach) अणु
		priv->dmach = rio_request_mport_dma(priv->md->mport);
		अगर (!priv->dmach) अणु
			/* Use शेष DMA channel अगर available */
			अगर (priv->md->dma_chan) अणु
				priv->dmach = priv->md->dma_chan;
				kref_get(&priv->md->dma_ref);
			पूर्ण अन्यथा अणु
				rmcd_error("Failed to get DMA channel");
				mutex_unlock(&priv->dma_lock);
				वापस -ENODEV;
			पूर्ण
		पूर्ण अन्यथा अगर (!priv->md->dma_chan) अणु
			/* Register शेष DMA channel अगर we करो not have one */
			priv->md->dma_chan = priv->dmach;
			kref_init(&priv->md->dma_ref);
			rmcd_debug(DMA, "Register DMA_chan %d as default",
				   priv->dmach->chan_id);
		पूर्ण

		kref_init(&priv->dma_ref);
		init_completion(&priv->comp);
	पूर्ण

	kref_get(&priv->dma_ref);
	mutex_unlock(&priv->dma_lock);
	वापस 0;
पूर्ण

अटल व्योम put_dma_channel(काष्ठा mport_cdev_priv *priv)
अणु
	kref_put(&priv->dma_ref, mport_release_dma);
पूर्ण

/*
 * DMA transfer functions
 */
अटल पूर्णांक करो_dma_request(काष्ठा mport_dma_req *req,
			  काष्ठा rio_transfer_io *xfer,
			  क्रमागत rio_transfer_sync sync, पूर्णांक nents)
अणु
	काष्ठा mport_cdev_priv *priv;
	काष्ठा sg_table *sgt;
	काष्ठा dma_chan *chan;
	काष्ठा dma_async_tx_descriptor *tx;
	dma_cookie_t cookie;
	अचिन्हित दीर्घ पंचांगo = msecs_to_jअगरfies(dma_समयout);
	क्रमागत dma_transfer_direction dir;
	दीर्घ wret;
	पूर्णांक ret = 0;

	priv = req->priv;
	sgt = &req->sgt;

	chan = priv->dmach;
	dir = (req->dir == DMA_FROM_DEVICE) ? DMA_DEV_TO_MEM : DMA_MEM_TO_DEV;

	rmcd_debug(DMA, "%s(%d) uses %s for DMA_%s",
		   current->comm, task_pid_nr(current),
		   dev_name(&chan->dev->device),
		   (dir == DMA_DEV_TO_MEM)?"READ":"WRITE");

	/* Initialize DMA transaction request */
	tx = prep_dma_xfer(chan, xfer, sgt, nents, dir,
			   DMA_CTRL_ACK | DMA_PREP_INTERRUPT);

	अगर (!tx) अणु
		rmcd_debug(DMA, "prep error for %s A:0x%llx L:0x%llx",
			(dir == DMA_DEV_TO_MEM)?"READ":"WRITE",
			xfer->rio_addr, xfer->length);
		ret = -EIO;
		जाओ err_out;
	पूर्ण अन्यथा अगर (IS_ERR(tx)) अणु
		ret = PTR_ERR(tx);
		rmcd_debug(DMA, "prep error %d for %s A:0x%llx L:0x%llx", ret,
			(dir == DMA_DEV_TO_MEM)?"READ":"WRITE",
			xfer->rio_addr, xfer->length);
		जाओ err_out;
	पूर्ण

	tx->callback = dma_xfer_callback;
	tx->callback_param = req;

	req->status = DMA_IN_PROGRESS;
	kref_get(&req->refcount);

	cookie = dmaengine_submit(tx);
	req->cookie = cookie;

	rmcd_debug(DMA, "pid=%d DMA_%s tx_cookie = %d", task_pid_nr(current),
		   (dir == DMA_DEV_TO_MEM)?"READ":"WRITE", cookie);

	अगर (dma_submit_error(cookie)) अणु
		rmcd_error("submit err=%d (addr:0x%llx len:0x%llx)",
			   cookie, xfer->rio_addr, xfer->length);
		kref_put(&req->refcount, dma_req_मुक्त);
		ret = -EIO;
		जाओ err_out;
	पूर्ण

	dma_async_issue_pending(chan);

	अगर (sync == RIO_TRANSFER_ASYNC) अणु
		spin_lock(&priv->req_lock);
		list_add_tail(&req->node, &priv->async_list);
		spin_unlock(&priv->req_lock);
		वापस cookie;
	पूर्ण अन्यथा अगर (sync == RIO_TRANSFER_FAF)
		वापस 0;

	wret = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&req->req_comp, पंचांगo);

	अगर (wret == 0) अणु
		/* Timeout on रुको occurred */
		rmcd_error("%s(%d) timed out waiting for DMA_%s %d",
		       current->comm, task_pid_nr(current),
		       (dir == DMA_DEV_TO_MEM)?"READ":"WRITE", cookie);
		वापस -ETIMEDOUT;
	पूर्ण अन्यथा अगर (wret == -ERESTARTSYS) अणु
		/* Wait_क्रम_completion was पूर्णांकerrupted by a संकेत but DMA may
		 * be in progress
		 */
		rmcd_error("%s(%d) wait for DMA_%s %d was interrupted",
			current->comm, task_pid_nr(current),
			(dir == DMA_DEV_TO_MEM)?"READ":"WRITE", cookie);
		वापस -EINTR;
	पूर्ण

	अगर (req->status != DMA_COMPLETE) अणु
		/* DMA transaction completion was संकेतed with error */
		rmcd_error("%s(%d) DMA_%s %d completed with status %d (ret=%d)",
			current->comm, task_pid_nr(current),
			(dir == DMA_DEV_TO_MEM)?"READ":"WRITE",
			cookie, req->status, ret);
		ret = -EIO;
	पूर्ण

err_out:
	वापस ret;
पूर्ण

/*
 * rio_dma_transfer() - Perक्रमm RapidIO DMA data transfer to/from
 *                      the remote RapidIO device
 * @filp: file poपूर्णांकer associated with the call
 * @transfer_mode: DMA transfer mode
 * @sync: synchronization mode
 * @dir: DMA transfer direction (DMA_MEM_TO_DEV = ग_लिखो OR
 *                               DMA_DEV_TO_MEM = पढ़ो)
 * @xfer: data transfer descriptor काष्ठाure
 */
अटल पूर्णांक
rio_dma_transfer(काष्ठा file *filp, u32 transfer_mode,
		 क्रमागत rio_transfer_sync sync, क्रमागत dma_data_direction dir,
		 काष्ठा rio_transfer_io *xfer)
अणु
	काष्ठा mport_cdev_priv *priv = filp->निजी_data;
	अचिन्हित दीर्घ nr_pages = 0;
	काष्ठा page **page_list = शून्य;
	काष्ठा mport_dma_req *req;
	काष्ठा mport_dev *md = priv->md;
	काष्ठा dma_chan *chan;
	पूर्णांक ret;
	पूर्णांक nents;

	अगर (xfer->length == 0)
		वापस -EINVAL;
	req = kzalloc(माप(*req), GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;

	ret = get_dma_channel(priv);
	अगर (ret) अणु
		kमुक्त(req);
		वापस ret;
	पूर्ण
	chan = priv->dmach;

	kref_init(&req->refcount);
	init_completion(&req->req_comp);
	req->dir = dir;
	req->filp = filp;
	req->priv = priv;
	req->dmach = chan;
	req->sync = sync;

	/*
	 * If parameter loc_addr != शून्य, we are transferring data from/to
	 * data buffer allocated in user-space: lock in memory user-space
	 * buffer pages and build an SG table क्रम DMA transfer request
	 *
	 * Otherwise (loc_addr == शून्य) contiguous kernel-space buffer is
	 * used क्रम DMA data transfers: build single entry SG table using
	 * offset within the पूर्णांकernal buffer specअगरied by handle parameter.
	 */
	अगर (xfer->loc_addr) अणु
		अचिन्हित पूर्णांक offset;
		दीर्घ pinned;

		offset = lower_32_bits(offset_in_page(xfer->loc_addr));
		nr_pages = PAGE_ALIGN(xfer->length + offset) >> PAGE_SHIFT;

		page_list = kदो_स्मृति_array(nr_pages,
					  माप(*page_list), GFP_KERNEL);
		अगर (page_list == शून्य) अणु
			ret = -ENOMEM;
			जाओ err_req;
		पूर्ण

		pinned = pin_user_pages_fast(
				(अचिन्हित दीर्घ)xfer->loc_addr & PAGE_MASK,
				nr_pages,
				dir == DMA_FROM_DEVICE ? FOLL_WRITE : 0,
				page_list);

		अगर (pinned != nr_pages) अणु
			अगर (pinned < 0) अणु
				rmcd_error("pin_user_pages_fast err=%ld",
					   pinned);
				nr_pages = 0;
			पूर्ण अन्यथा अणु
				rmcd_error("pinned %ld out of %ld pages",
					   pinned, nr_pages);
				/*
				 * Set nr_pages up to mean "how many pages to unpin, in
				 * the error handler:
				 */
				nr_pages = pinned;
			पूर्ण
			ret = -EFAULT;
			जाओ err_pg;
		पूर्ण

		ret = sg_alloc_table_from_pages(&req->sgt, page_list, nr_pages,
					offset, xfer->length, GFP_KERNEL);
		अगर (ret) अणु
			rmcd_error("sg_alloc_table failed with err=%d", ret);
			जाओ err_pg;
		पूर्ण

		req->page_list = page_list;
		req->nr_pages = nr_pages;
	पूर्ण अन्यथा अणु
		dma_addr_t baddr;
		काष्ठा rio_mport_mapping *map;

		baddr = (dma_addr_t)xfer->handle;

		mutex_lock(&md->buf_mutex);
		list_क्रम_each_entry(map, &md->mappings, node) अणु
			अगर (baddr >= map->phys_addr &&
			    baddr < (map->phys_addr + map->size)) अणु
				kref_get(&map->ref);
				req->map = map;
				अवरोध;
			पूर्ण
		पूर्ण
		mutex_unlock(&md->buf_mutex);

		अगर (req->map == शून्य) अणु
			ret = -ENOMEM;
			जाओ err_req;
		पूर्ण

		अगर (xfer->length + xfer->offset > map->size) अणु
			ret = -EINVAL;
			जाओ err_req;
		पूर्ण

		ret = sg_alloc_table(&req->sgt, 1, GFP_KERNEL);
		अगर (unlikely(ret)) अणु
			rmcd_error("sg_alloc_table failed for internal buf");
			जाओ err_req;
		पूर्ण

		sg_set_buf(req->sgt.sgl,
			   map->virt_addr + (baddr - map->phys_addr) +
				xfer->offset, xfer->length);
	पूर्ण

	nents = dma_map_sg(chan->device->dev,
			   req->sgt.sgl, req->sgt.nents, dir);
	अगर (nents == 0) अणु
		rmcd_error("Failed to map SG list");
		ret = -EFAULT;
		जाओ err_pg;
	पूर्ण

	ret = करो_dma_request(req, xfer, sync, nents);

	अगर (ret >= 0) अणु
		अगर (sync == RIO_TRANSFER_ASYNC)
			वापस ret; /* वापस ASYNC cookie */
	पूर्ण अन्यथा अणु
		rmcd_debug(DMA, "do_dma_request failed with err=%d", ret);
	पूर्ण

err_pg:
	अगर (!req->page_list) अणु
		unpin_user_pages(page_list, nr_pages);
		kमुक्त(page_list);
	पूर्ण
err_req:
	kref_put(&req->refcount, dma_req_मुक्त);
	वापस ret;
पूर्ण

अटल पूर्णांक rio_mport_transfer_ioctl(काष्ठा file *filp, व्योम __user *arg)
अणु
	काष्ठा mport_cdev_priv *priv = filp->निजी_data;
	काष्ठा rio_transaction transaction;
	काष्ठा rio_transfer_io *transfer;
	क्रमागत dma_data_direction dir;
	पूर्णांक i, ret = 0;

	अगर (unlikely(copy_from_user(&transaction, arg, माप(transaction))))
		वापस -EFAULT;

	अगर (transaction.count != 1) /* only single transfer क्रम now */
		वापस -EINVAL;

	अगर ((transaction.transfer_mode &
	     priv->md->properties.transfer_mode) == 0)
		वापस -ENODEV;

	transfer = vदो_स्मृति(array_size(माप(*transfer), transaction.count));
	अगर (!transfer)
		वापस -ENOMEM;

	अगर (unlikely(copy_from_user(transfer,
				    (व्योम __user *)(uपूर्णांकptr_t)transaction.block,
				    array_size(माप(*transfer), transaction.count)))) अणु
		ret = -EFAULT;
		जाओ out_मुक्त;
	पूर्ण

	dir = (transaction.dir == RIO_TRANSFER_सूची_READ) ?
					DMA_FROM_DEVICE : DMA_TO_DEVICE;
	क्रम (i = 0; i < transaction.count && ret == 0; i++)
		ret = rio_dma_transfer(filp, transaction.transfer_mode,
			transaction.sync, dir, &transfer[i]);

	अगर (unlikely(copy_to_user((व्योम __user *)(uपूर्णांकptr_t)transaction.block,
				  transfer,
				  array_size(माप(*transfer), transaction.count))))
		ret = -EFAULT;

out_मुक्त:
	vमुक्त(transfer);

	वापस ret;
पूर्ण

अटल पूर्णांक rio_mport_रुको_क्रम_async_dma(काष्ठा file *filp, व्योम __user *arg)
अणु
	काष्ठा mport_cdev_priv *priv;
	काष्ठा rio_async_tx_रुको w_param;
	काष्ठा mport_dma_req *req;
	dma_cookie_t cookie;
	अचिन्हित दीर्घ पंचांगo;
	दीर्घ wret;
	पूर्णांक found = 0;
	पूर्णांक ret;

	priv = (काष्ठा mport_cdev_priv *)filp->निजी_data;

	अगर (unlikely(copy_from_user(&w_param, arg, माप(w_param))))
		वापस -EFAULT;

	cookie = w_param.token;
	अगर (w_param.समयout)
		पंचांगo = msecs_to_jअगरfies(w_param.समयout);
	अन्यथा /* Use शेष DMA समयout */
		पंचांगo = msecs_to_jअगरfies(dma_समयout);

	spin_lock(&priv->req_lock);
	list_क्रम_each_entry(req, &priv->async_list, node) अणु
		अगर (req->cookie == cookie) अणु
			list_del(&req->node);
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&priv->req_lock);

	अगर (!found)
		वापस -EAGAIN;

	wret = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&req->req_comp, पंचांगo);

	अगर (wret == 0) अणु
		/* Timeout on रुको occurred */
		rmcd_error("%s(%d) timed out waiting for ASYNC DMA_%s",
		       current->comm, task_pid_nr(current),
		       (req->dir == DMA_FROM_DEVICE)?"READ":"WRITE");
		ret = -ETIMEDOUT;
		जाओ err_पंचांगo;
	पूर्ण अन्यथा अगर (wret == -ERESTARTSYS) अणु
		/* Wait_क्रम_completion was पूर्णांकerrupted by a संकेत but DMA may
		 * be still in progress
		 */
		rmcd_error("%s(%d) wait for ASYNC DMA_%s was interrupted",
			current->comm, task_pid_nr(current),
			(req->dir == DMA_FROM_DEVICE)?"READ":"WRITE");
		ret = -EINTR;
		जाओ err_पंचांगo;
	पूर्ण

	अगर (req->status != DMA_COMPLETE) अणु
		/* DMA transaction completion संकेतed with transfer error */
		rmcd_error("%s(%d) ASYNC DMA_%s completion with status %d",
			current->comm, task_pid_nr(current),
			(req->dir == DMA_FROM_DEVICE)?"READ":"WRITE",
			req->status);
		ret = -EIO;
	पूर्ण अन्यथा
		ret = 0;

	अगर (req->status != DMA_IN_PROGRESS && req->status != DMA_PAUSED)
		kref_put(&req->refcount, dma_req_मुक्त);

	वापस ret;

err_पंचांगo:
	/* Return request back पूर्णांकo async queue */
	spin_lock(&priv->req_lock);
	list_add_tail(&req->node, &priv->async_list);
	spin_unlock(&priv->req_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक rio_mport_create_dma_mapping(काष्ठा mport_dev *md, काष्ठा file *filp,
			u64 size, काष्ठा rio_mport_mapping **mapping)
अणु
	काष्ठा rio_mport_mapping *map;

	map = kzalloc(माप(*map), GFP_KERNEL);
	अगर (map == शून्य)
		वापस -ENOMEM;

	map->virt_addr = dma_alloc_coherent(md->mport->dev.parent, size,
					    &map->phys_addr, GFP_KERNEL);
	अगर (map->virt_addr == शून्य) अणु
		kमुक्त(map);
		वापस -ENOMEM;
	पूर्ण

	map->dir = MAP_DMA;
	map->size = size;
	map->filp = filp;
	map->md = md;
	kref_init(&map->ref);
	mutex_lock(&md->buf_mutex);
	list_add_tail(&map->node, &md->mappings);
	mutex_unlock(&md->buf_mutex);
	*mapping = map;

	वापस 0;
पूर्ण

अटल पूर्णांक rio_mport_alloc_dma(काष्ठा file *filp, व्योम __user *arg)
अणु
	काष्ठा mport_cdev_priv *priv = filp->निजी_data;
	काष्ठा mport_dev *md = priv->md;
	काष्ठा rio_dma_mem map;
	काष्ठा rio_mport_mapping *mapping = शून्य;
	पूर्णांक ret;

	अगर (unlikely(copy_from_user(&map, arg, माप(map))))
		वापस -EFAULT;

	ret = rio_mport_create_dma_mapping(md, filp, map.length, &mapping);
	अगर (ret)
		वापस ret;

	map.dma_handle = mapping->phys_addr;

	अगर (unlikely(copy_to_user(arg, &map, माप(map)))) अणु
		mutex_lock(&md->buf_mutex);
		kref_put(&mapping->ref, mport_release_mapping);
		mutex_unlock(&md->buf_mutex);
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rio_mport_मुक्त_dma(काष्ठा file *filp, व्योम __user *arg)
अणु
	काष्ठा mport_cdev_priv *priv = filp->निजी_data;
	काष्ठा mport_dev *md = priv->md;
	u64 handle;
	पूर्णांक ret = -EFAULT;
	काष्ठा rio_mport_mapping *map, *_map;

	अगर (copy_from_user(&handle, arg, माप(handle)))
		वापस -EFAULT;
	rmcd_debug(EXIT, "filp=%p", filp);

	mutex_lock(&md->buf_mutex);
	list_क्रम_each_entry_safe(map, _map, &md->mappings, node) अणु
		अगर (map->dir == MAP_DMA && map->phys_addr == handle &&
		    map->filp == filp) अणु
			kref_put(&map->ref, mport_release_mapping);
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&md->buf_mutex);

	अगर (ret == -EFAULT) अणु
		rmcd_debug(DMA, "ERR no matching mapping");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक rio_mport_transfer_ioctl(काष्ठा file *filp, व्योम *arg)
अणु
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक rio_mport_रुको_क्रम_async_dma(काष्ठा file *filp, व्योम __user *arg)
अणु
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक rio_mport_alloc_dma(काष्ठा file *filp, व्योम __user *arg)
अणु
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक rio_mport_मुक्त_dma(काष्ठा file *filp, व्योम __user *arg)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर /* CONFIG_RAPIDIO_DMA_ENGINE */

/*
 * Inbound/outbound memory mapping functions
 */

अटल पूर्णांक
rio_mport_create_inbound_mapping(काष्ठा mport_dev *md, काष्ठा file *filp,
				u64 raddr, u64 size,
				काष्ठा rio_mport_mapping **mapping)
अणु
	काष्ठा rio_mport *mport = md->mport;
	काष्ठा rio_mport_mapping *map;
	पूर्णांक ret;

	/* rio_map_inb_region() accepts u32 size */
	अगर (size > 0xffffffff)
		वापस -EINVAL;

	map = kzalloc(माप(*map), GFP_KERNEL);
	अगर (map == शून्य)
		वापस -ENOMEM;

	map->virt_addr = dma_alloc_coherent(mport->dev.parent, size,
					    &map->phys_addr, GFP_KERNEL);
	अगर (map->virt_addr == शून्य) अणु
		ret = -ENOMEM;
		जाओ err_dma_alloc;
	पूर्ण

	अगर (raddr == RIO_MAP_ANY_ADDR)
		raddr = map->phys_addr;
	ret = rio_map_inb_region(mport, map->phys_addr, raddr, (u32)size, 0);
	अगर (ret < 0)
		जाओ err_map_inb;

	map->dir = MAP_INBOUND;
	map->rio_addr = raddr;
	map->size = size;
	map->filp = filp;
	map->md = md;
	kref_init(&map->ref);
	mutex_lock(&md->buf_mutex);
	list_add_tail(&map->node, &md->mappings);
	mutex_unlock(&md->buf_mutex);
	*mapping = map;
	वापस 0;

err_map_inb:
	dma_मुक्त_coherent(mport->dev.parent, size,
			  map->virt_addr, map->phys_addr);
err_dma_alloc:
	kमुक्त(map);
	वापस ret;
पूर्ण

अटल पूर्णांक
rio_mport_get_inbound_mapping(काष्ठा mport_dev *md, काष्ठा file *filp,
			      u64 raddr, u64 size,
			      काष्ठा rio_mport_mapping **mapping)
अणु
	काष्ठा rio_mport_mapping *map;
	पूर्णांक err = -ENOMEM;

	अगर (raddr == RIO_MAP_ANY_ADDR)
		जाओ get_new;

	mutex_lock(&md->buf_mutex);
	list_क्रम_each_entry(map, &md->mappings, node) अणु
		अगर (map->dir != MAP_INBOUND)
			जारी;
		अगर (raddr == map->rio_addr && size == map->size) अणु
			/* allow exact match only */
			*mapping = map;
			err = 0;
			अवरोध;
		पूर्ण अन्यथा अगर (raddr < (map->rio_addr + map->size - 1) &&
			   (raddr + size) > map->rio_addr) अणु
			err = -EBUSY;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&md->buf_mutex);

	अगर (err != -ENOMEM)
		वापस err;
get_new:
	/* not found, create new */
	वापस rio_mport_create_inbound_mapping(md, filp, raddr, size, mapping);
पूर्ण

अटल पूर्णांक rio_mport_map_inbound(काष्ठा file *filp, व्योम __user *arg)
अणु
	काष्ठा mport_cdev_priv *priv = filp->निजी_data;
	काष्ठा mport_dev *md = priv->md;
	काष्ठा rio_mmap map;
	काष्ठा rio_mport_mapping *mapping = शून्य;
	पूर्णांक ret;

	अगर (!md->mport->ops->map_inb)
		वापस -EPROTONOSUPPORT;
	अगर (unlikely(copy_from_user(&map, arg, माप(map))))
		वापस -EFAULT;

	rmcd_debug(IBW, "%s filp=%p", dev_name(&priv->md->dev), filp);

	ret = rio_mport_get_inbound_mapping(md, filp, map.rio_addr,
					    map.length, &mapping);
	अगर (ret)
		वापस ret;

	map.handle = mapping->phys_addr;
	map.rio_addr = mapping->rio_addr;

	अगर (unlikely(copy_to_user(arg, &map, माप(map)))) अणु
		/* Delete mapping अगर it was created by this request */
		अगर (ret == 0 && mapping->filp == filp) अणु
			mutex_lock(&md->buf_mutex);
			kref_put(&mapping->ref, mport_release_mapping);
			mutex_unlock(&md->buf_mutex);
		पूर्ण
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * rio_mport_inbound_मुक्त() - unmap from RapidIO address space and मुक्त
 *                    previously allocated inbound DMA coherent buffer
 * @priv: driver निजी data
 * @arg:  buffer handle वापसed by allocation routine
 */
अटल पूर्णांक rio_mport_inbound_मुक्त(काष्ठा file *filp, व्योम __user *arg)
अणु
	काष्ठा mport_cdev_priv *priv = filp->निजी_data;
	काष्ठा mport_dev *md = priv->md;
	u64 handle;
	काष्ठा rio_mport_mapping *map, *_map;

	rmcd_debug(IBW, "%s filp=%p", dev_name(&priv->md->dev), filp);

	अगर (!md->mport->ops->unmap_inb)
		वापस -EPROTONOSUPPORT;

	अगर (copy_from_user(&handle, arg, माप(handle)))
		वापस -EFAULT;

	mutex_lock(&md->buf_mutex);
	list_क्रम_each_entry_safe(map, _map, &md->mappings, node) अणु
		अगर (map->dir == MAP_INBOUND && map->phys_addr == handle) अणु
			अगर (map->filp == filp) अणु
				map->filp = शून्य;
				kref_put(&map->ref, mport_release_mapping);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&md->buf_mutex);

	वापस 0;
पूर्ण

/*
 * मुख्यt_port_idx_get() - Get the port index of the mport instance
 * @priv: driver निजी data
 * @arg:  port index
 */
अटल पूर्णांक मुख्यt_port_idx_get(काष्ठा mport_cdev_priv *priv, व्योम __user *arg)
अणु
	काष्ठा mport_dev *md = priv->md;
	u32 port_idx = md->mport->index;

	rmcd_debug(MPORT, "port_index=%d", port_idx);

	अगर (copy_to_user(arg, &port_idx, माप(port_idx)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक rio_mport_add_event(काष्ठा mport_cdev_priv *priv,
			       काष्ठा rio_event *event)
अणु
	पूर्णांक overflow;

	अगर (!(priv->event_mask & event->header))
		वापस -EACCES;

	spin_lock(&priv->fअगरo_lock);
	overflow = kfअगरo_avail(&priv->event_fअगरo) < माप(*event)
		|| kfअगरo_in(&priv->event_fअगरo, (अचिन्हित अक्षर *)event,
			माप(*event)) != माप(*event);
	spin_unlock(&priv->fअगरo_lock);

	wake_up_पूर्णांकerruptible(&priv->event_rx_रुको);

	अगर (overflow) अणु
		dev_warn(&priv->md->dev, DRV_NAME ": event fifo overflow\n");
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rio_mport_करोorbell_handler(काष्ठा rio_mport *mport, व्योम *dev_id,
				       u16 src, u16 dst, u16 info)
अणु
	काष्ठा mport_dev *data = dev_id;
	काष्ठा mport_cdev_priv *priv;
	काष्ठा rio_mport_db_filter *db_filter;
	काष्ठा rio_event event;
	पूर्णांक handled;

	event.header = RIO_DOORBELL;
	event.u.करोorbell.rioid = src;
	event.u.करोorbell.payload = info;

	handled = 0;
	spin_lock(&data->db_lock);
	list_क्रम_each_entry(db_filter, &data->करोorbells, data_node) अणु
		अगर (((db_filter->filter.rioid == RIO_INVALID_DESTID ||
		      db_filter->filter.rioid == src)) &&
		      info >= db_filter->filter.low &&
		      info <= db_filter->filter.high) अणु
			priv = db_filter->priv;
			rio_mport_add_event(priv, &event);
			handled = 1;
		पूर्ण
	पूर्ण
	spin_unlock(&data->db_lock);

	अगर (!handled)
		dev_warn(&data->dev,
			"%s: spurious DB received from 0x%x, info=0x%04x\n",
			__func__, src, info);
पूर्ण

अटल पूर्णांक rio_mport_add_db_filter(काष्ठा mport_cdev_priv *priv,
				   व्योम __user *arg)
अणु
	काष्ठा mport_dev *md = priv->md;
	काष्ठा rio_mport_db_filter *db_filter;
	काष्ठा rio_करोorbell_filter filter;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (copy_from_user(&filter, arg, माप(filter)))
		वापस -EFAULT;

	अगर (filter.low > filter.high)
		वापस -EINVAL;

	ret = rio_request_inb_dbell(md->mport, md, filter.low, filter.high,
				    rio_mport_करोorbell_handler);
	अगर (ret) अणु
		rmcd_error("%s failed to register IBDB, err=%d",
			   dev_name(&md->dev), ret);
		वापस ret;
	पूर्ण

	db_filter = kzalloc(माप(*db_filter), GFP_KERNEL);
	अगर (db_filter == शून्य) अणु
		rio_release_inb_dbell(md->mport, filter.low, filter.high);
		वापस -ENOMEM;
	पूर्ण

	db_filter->filter = filter;
	db_filter->priv = priv;
	spin_lock_irqsave(&md->db_lock, flags);
	list_add_tail(&db_filter->priv_node, &priv->db_filters);
	list_add_tail(&db_filter->data_node, &md->करोorbells);
	spin_unlock_irqrestore(&md->db_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम rio_mport_delete_db_filter(काष्ठा rio_mport_db_filter *db_filter)
अणु
	list_del(&db_filter->data_node);
	list_del(&db_filter->priv_node);
	kमुक्त(db_filter);
पूर्ण

अटल पूर्णांक rio_mport_हटाओ_db_filter(काष्ठा mport_cdev_priv *priv,
				      व्योम __user *arg)
अणु
	काष्ठा rio_mport_db_filter *db_filter;
	काष्ठा rio_करोorbell_filter filter;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -EINVAL;

	अगर (copy_from_user(&filter, arg, माप(filter)))
		वापस -EFAULT;

	अगर (filter.low > filter.high)
		वापस -EINVAL;

	spin_lock_irqsave(&priv->md->db_lock, flags);
	list_क्रम_each_entry(db_filter, &priv->db_filters, priv_node) अणु
		अगर (db_filter->filter.rioid == filter.rioid &&
		    db_filter->filter.low == filter.low &&
		    db_filter->filter.high == filter.high) अणु
			rio_mport_delete_db_filter(db_filter);
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&priv->md->db_lock, flags);

	अगर (!ret)
		rio_release_inb_dbell(priv->md->mport, filter.low, filter.high);

	वापस ret;
पूर्ण

अटल पूर्णांक rio_mport_match_pw(जोड़ rio_pw_msg *msg,
			      काष्ठा rio_pw_filter *filter)
अणु
	अगर ((msg->em.comptag & filter->mask) < filter->low ||
		(msg->em.comptag & filter->mask) > filter->high)
		वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक rio_mport_pw_handler(काष्ठा rio_mport *mport, व्योम *context,
				जोड़ rio_pw_msg *msg, पूर्णांक step)
अणु
	काष्ठा mport_dev *md = context;
	काष्ठा mport_cdev_priv *priv;
	काष्ठा rio_mport_pw_filter *pw_filter;
	काष्ठा rio_event event;
	पूर्णांक handled;

	event.header = RIO_PORTWRITE;
	स_नकल(event.u.portग_लिखो.payload, msg->raw, RIO_PW_MSG_SIZE);

	handled = 0;
	spin_lock(&md->pw_lock);
	list_क्रम_each_entry(pw_filter, &md->portग_लिखोs, md_node) अणु
		अगर (rio_mport_match_pw(msg, &pw_filter->filter)) अणु
			priv = pw_filter->priv;
			rio_mport_add_event(priv, &event);
			handled = 1;
		पूर्ण
	पूर्ण
	spin_unlock(&md->pw_lock);

	अगर (!handled) अणु
		prपूर्णांकk_ratelimited(KERN_WARNING DRV_NAME
			": mport%d received spurious PW from 0x%08x\n",
			mport->id, msg->em.comptag);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rio_mport_add_pw_filter(काष्ठा mport_cdev_priv *priv,
				   व्योम __user *arg)
अणु
	काष्ठा mport_dev *md = priv->md;
	काष्ठा rio_mport_pw_filter *pw_filter;
	काष्ठा rio_pw_filter filter;
	अचिन्हित दीर्घ flags;
	पूर्णांक hadd = 0;

	अगर (copy_from_user(&filter, arg, माप(filter)))
		वापस -EFAULT;

	pw_filter = kzalloc(माप(*pw_filter), GFP_KERNEL);
	अगर (pw_filter == शून्य)
		वापस -ENOMEM;

	pw_filter->filter = filter;
	pw_filter->priv = priv;
	spin_lock_irqsave(&md->pw_lock, flags);
	अगर (list_empty(&md->portग_लिखोs))
		hadd = 1;
	list_add_tail(&pw_filter->priv_node, &priv->pw_filters);
	list_add_tail(&pw_filter->md_node, &md->portग_लिखोs);
	spin_unlock_irqrestore(&md->pw_lock, flags);

	अगर (hadd) अणु
		पूर्णांक ret;

		ret = rio_add_mport_pw_handler(md->mport, md,
					       rio_mport_pw_handler);
		अगर (ret) अणु
			dev_err(&md->dev,
				"%s: failed to add IB_PW handler, err=%d\n",
				__func__, ret);
			वापस ret;
		पूर्ण
		rio_pw_enable(md->mport, 1);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rio_mport_delete_pw_filter(काष्ठा rio_mport_pw_filter *pw_filter)
अणु
	list_del(&pw_filter->md_node);
	list_del(&pw_filter->priv_node);
	kमुक्त(pw_filter);
पूर्ण

अटल पूर्णांक rio_mport_match_pw_filter(काष्ठा rio_pw_filter *a,
				     काष्ठा rio_pw_filter *b)
अणु
	अगर ((a->mask == b->mask) && (a->low == b->low) && (a->high == b->high))
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक rio_mport_हटाओ_pw_filter(काष्ठा mport_cdev_priv *priv,
				      व्योम __user *arg)
अणु
	काष्ठा mport_dev *md = priv->md;
	काष्ठा rio_mport_pw_filter *pw_filter;
	काष्ठा rio_pw_filter filter;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -EINVAL;
	पूर्णांक hdel = 0;

	अगर (copy_from_user(&filter, arg, माप(filter)))
		वापस -EFAULT;

	spin_lock_irqsave(&md->pw_lock, flags);
	list_क्रम_each_entry(pw_filter, &priv->pw_filters, priv_node) अणु
		अगर (rio_mport_match_pw_filter(&pw_filter->filter, &filter)) अणु
			rio_mport_delete_pw_filter(pw_filter);
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (list_empty(&md->portग_लिखोs))
		hdel = 1;
	spin_unlock_irqrestore(&md->pw_lock, flags);

	अगर (hdel) अणु
		rio_del_mport_pw_handler(md->mport, priv->md,
					 rio_mport_pw_handler);
		rio_pw_enable(md->mport, 0);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * rio_release_dev - release routine क्रम kernel RIO device object
 * @dev: kernel device object associated with a RIO device काष्ठाure
 *
 * Frees a RIO device काष्ठा associated a RIO device काष्ठा.
 * The RIO device काष्ठा is मुक्तd.
 */
अटल व्योम rio_release_dev(काष्ठा device *dev)
अणु
	काष्ठा rio_dev *rdev;

	rdev = to_rio_dev(dev);
	pr_info(DRV_PREFIX "%s: %s\n", __func__, rio_name(rdev));
	kमुक्त(rdev);
पूर्ण


अटल व्योम rio_release_net(काष्ठा device *dev)
अणु
	काष्ठा rio_net *net;

	net = to_rio_net(dev);
	rmcd_debug(RDEV, "net_%d", net->id);
	kमुक्त(net);
पूर्ण


/*
 * rio_mport_add_riodev - creates a kernel RIO device object
 *
 * Allocates a RIO device data काष्ठाure and initializes required fields based
 * on device's configuration space contents.
 * If the device has चयन capabilities, then a चयन specअगरic portion is
 * allocated and configured.
 */
अटल पूर्णांक rio_mport_add_riodev(काष्ठा mport_cdev_priv *priv,
				   व्योम __user *arg)
अणु
	काष्ठा mport_dev *md = priv->md;
	काष्ठा rio_rdev_info dev_info;
	काष्ठा rio_dev *rdev;
	काष्ठा rio_चयन *rचयन = शून्य;
	काष्ठा rio_mport *mport;
	काष्ठा device *dev;
	माप_प्रकार size;
	u32 rval;
	u32 swpinfo = 0;
	u16 destid;
	u8 hopcount;
	पूर्णांक err;

	अगर (copy_from_user(&dev_info, arg, माप(dev_info)))
		वापस -EFAULT;
	dev_info.name[माप(dev_info.name) - 1] = '\0';

	rmcd_debug(RDEV, "name:%s ct:0x%x did:0x%x hc:0x%x", dev_info.name,
		   dev_info.comptag, dev_info.destid, dev_info.hopcount);

	dev = bus_find_device_by_name(&rio_bus_type, शून्य, dev_info.name);
	अगर (dev) अणु
		rmcd_debug(RDEV, "device %s already exists", dev_info.name);
		put_device(dev);
		वापस -EEXIST;
	पूर्ण

	size = माप(*rdev);
	mport = md->mport;
	destid = dev_info.destid;
	hopcount = dev_info.hopcount;

	अगर (rio_mport_पढ़ो_config_32(mport, destid, hopcount,
				     RIO_PEF_CAR, &rval))
		वापस -EIO;

	अगर (rval & RIO_PEF_SWITCH) अणु
		rio_mport_पढ़ो_config_32(mport, destid, hopcount,
					 RIO_SWP_INFO_CAR, &swpinfo);
		size += काष्ठा_size(rचयन, nextdev, RIO_GET_TOTAL_PORTS(swpinfo));
	पूर्ण

	rdev = kzalloc(size, GFP_KERNEL);
	अगर (rdev == शून्य)
		वापस -ENOMEM;

	अगर (mport->net == शून्य) अणु
		काष्ठा rio_net *net;

		net = rio_alloc_net(mport);
		अगर (!net) अणु
			err = -ENOMEM;
			rmcd_debug(RDEV, "failed to allocate net object");
			जाओ cleanup;
		पूर्ण

		net->id = mport->id;
		net->hport = mport;
		dev_set_name(&net->dev, "rnet_%d", net->id);
		net->dev.parent = &mport->dev;
		net->dev.release = rio_release_net;
		err = rio_add_net(net);
		अगर (err) अणु
			rmcd_debug(RDEV, "failed to register net, err=%d", err);
			kमुक्त(net);
			जाओ cleanup;
		पूर्ण
	पूर्ण

	rdev->net = mport->net;
	rdev->pef = rval;
	rdev->swpinfo = swpinfo;
	rio_mport_पढ़ो_config_32(mport, destid, hopcount,
				 RIO_DEV_ID_CAR, &rval);
	rdev->did = rval >> 16;
	rdev->vid = rval & 0xffff;
	rio_mport_पढ़ो_config_32(mport, destid, hopcount, RIO_DEV_INFO_CAR,
				 &rdev->device_rev);
	rio_mport_पढ़ो_config_32(mport, destid, hopcount, RIO_ASM_ID_CAR,
				 &rval);
	rdev->यंत्र_did = rval >> 16;
	rdev->यंत्र_vid = rval & 0xffff;
	rio_mport_पढ़ो_config_32(mport, destid, hopcount, RIO_ASM_INFO_CAR,
				 &rval);
	rdev->यंत्र_rev = rval >> 16;

	अगर (rdev->pef & RIO_PEF_EXT_FEATURES) अणु
		rdev->efptr = rval & 0xffff;
		rdev->phys_efptr = rio_mport_get_physefb(mport, 0, destid,
						hopcount, &rdev->phys_rmap);

		rdev->em_efptr = rio_mport_get_feature(mport, 0, destid,
						hopcount, RIO_EFB_ERR_MGMNT);
	पूर्ण

	rio_mport_पढ़ो_config_32(mport, destid, hopcount, RIO_SRC_OPS_CAR,
				 &rdev->src_ops);
	rio_mport_पढ़ो_config_32(mport, destid, hopcount, RIO_DST_OPS_CAR,
				 &rdev->dst_ops);

	rdev->comp_tag = dev_info.comptag;
	rdev->destid = destid;
	/* hopcount is stored as specअगरied by a caller, regardles of EP or SW */
	rdev->hopcount = hopcount;

	अगर (rdev->pef & RIO_PEF_SWITCH) अणु
		rचयन = rdev->rचयन;
		rचयन->route_table = शून्य;
	पूर्ण

	अगर (म_माप(dev_info.name))
		dev_set_name(&rdev->dev, "%s", dev_info.name);
	अन्यथा अगर (rdev->pef & RIO_PEF_SWITCH)
		dev_set_name(&rdev->dev, "%02x:s:%04x", mport->id,
			     rdev->comp_tag & RIO_CTAG_UDEVID);
	अन्यथा
		dev_set_name(&rdev->dev, "%02x:e:%04x", mport->id,
			     rdev->comp_tag & RIO_CTAG_UDEVID);

	INIT_LIST_HEAD(&rdev->net_list);
	rdev->dev.parent = &mport->net->dev;
	rio_attach_device(rdev);
	rdev->dev.release = rio_release_dev;

	अगर (rdev->dst_ops & RIO_DST_OPS_DOORBELL)
		rio_init_dbell_res(&rdev->riores[RIO_DOORBELL_RESOURCE],
				   0, 0xffff);
	err = rio_add_device(rdev);
	अगर (err)
		जाओ cleanup;
	rio_dev_get(rdev);

	वापस 0;
cleanup:
	kमुक्त(rdev);
	वापस err;
पूर्ण

अटल पूर्णांक rio_mport_del_riodev(काष्ठा mport_cdev_priv *priv, व्योम __user *arg)
अणु
	काष्ठा rio_rdev_info dev_info;
	काष्ठा rio_dev *rdev = शून्य;
	काष्ठा device  *dev;
	काष्ठा rio_mport *mport;
	काष्ठा rio_net *net;

	अगर (copy_from_user(&dev_info, arg, माप(dev_info)))
		वापस -EFAULT;
	dev_info.name[माप(dev_info.name) - 1] = '\0';

	mport = priv->md->mport;

	/* If device name is specअगरied, removal by name has priority */
	अगर (म_माप(dev_info.name)) अणु
		dev = bus_find_device_by_name(&rio_bus_type, शून्य,
					      dev_info.name);
		अगर (dev)
			rdev = to_rio_dev(dev);
	पूर्ण अन्यथा अणु
		करो अणु
			rdev = rio_get_comptag(dev_info.comptag, rdev);
			अगर (rdev && rdev->dev.parent == &mport->net->dev &&
			    rdev->destid == dev_info.destid &&
			    rdev->hopcount == dev_info.hopcount)
				अवरोध;
		पूर्ण जबतक (rdev);
	पूर्ण

	अगर (!rdev) अणु
		rmcd_debug(RDEV,
			"device name:%s ct:0x%x did:0x%x hc:0x%x not found",
			dev_info.name, dev_info.comptag, dev_info.destid,
			dev_info.hopcount);
		वापस -ENODEV;
	पूर्ण

	net = rdev->net;
	rio_dev_put(rdev);
	rio_del_device(rdev, RIO_DEVICE_SHUTDOWN);

	अगर (list_empty(&net->devices)) अणु
		rio_मुक्त_net(net);
		mport->net = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Mport cdev management
 */

/*
 * mport_cdev_खोलो() - Open अक्षरacter device (mport)
 */
अटल पूर्णांक mport_cdev_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	पूर्णांक ret;
	पूर्णांक minor = iminor(inode);
	काष्ठा mport_dev *chdev;
	काष्ठा mport_cdev_priv *priv;

	/* Test क्रम valid device */
	अगर (minor >= RIO_MAX_MPORTS) अणु
		rmcd_error("Invalid minor device number");
		वापस -EINVAL;
	पूर्ण

	chdev = container_of(inode->i_cdev, काष्ठा mport_dev, cdev);

	rmcd_debug(INIT, "%s filp=%p", dev_name(&chdev->dev), filp);

	अगर (atomic_पढ़ो(&chdev->active) == 0)
		वापस -ENODEV;

	get_device(&chdev->dev);

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv) अणु
		put_device(&chdev->dev);
		वापस -ENOMEM;
	पूर्ण

	priv->md = chdev;

	mutex_lock(&chdev->file_mutex);
	list_add_tail(&priv->list, &chdev->file_list);
	mutex_unlock(&chdev->file_mutex);

	INIT_LIST_HEAD(&priv->db_filters);
	INIT_LIST_HEAD(&priv->pw_filters);
	spin_lock_init(&priv->fअगरo_lock);
	init_रुकोqueue_head(&priv->event_rx_रुको);
	ret = kfअगरo_alloc(&priv->event_fअगरo,
			  माप(काष्ठा rio_event) * MPORT_EVENT_DEPTH,
			  GFP_KERNEL);
	अगर (ret < 0) अणु
		dev_err(&chdev->dev, DRV_NAME ": kfifo_alloc failed\n");
		ret = -ENOMEM;
		जाओ err_fअगरo;
	पूर्ण

#अगर_घोषित CONFIG_RAPIDIO_DMA_ENGINE
	INIT_LIST_HEAD(&priv->async_list);
	spin_lock_init(&priv->req_lock);
	mutex_init(&priv->dma_lock);
#पूर्ण_अगर

	filp->निजी_data = priv;
	जाओ out;
err_fअगरo:
	kमुक्त(priv);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक mport_cdev_fasync(पूर्णांक fd, काष्ठा file *filp, पूर्णांक mode)
अणु
	काष्ठा mport_cdev_priv *priv = filp->निजी_data;

	वापस fasync_helper(fd, filp, mode, &priv->async_queue);
पूर्ण

#अगर_घोषित CONFIG_RAPIDIO_DMA_ENGINE
अटल व्योम mport_cdev_release_dma(काष्ठा file *filp)
अणु
	काष्ठा mport_cdev_priv *priv = filp->निजी_data;
	काष्ठा mport_dev *md;
	काष्ठा mport_dma_req *req, *req_next;
	अचिन्हित दीर्घ पंचांगo = msecs_to_jअगरfies(dma_समयout);
	दीर्घ wret;
	LIST_HEAD(list);

	rmcd_debug(EXIT, "from filp=%p %s(%d)",
		   filp, current->comm, task_pid_nr(current));

	अगर (!priv->dmach) अणु
		rmcd_debug(EXIT, "No DMA channel for filp=%p", filp);
		वापस;
	पूर्ण

	md = priv->md;

	spin_lock(&priv->req_lock);
	अगर (!list_empty(&priv->async_list)) अणु
		rmcd_debug(EXIT, "async list not empty filp=%p %s(%d)",
			   filp, current->comm, task_pid_nr(current));
		list_splice_init(&priv->async_list, &list);
	पूर्ण
	spin_unlock(&priv->req_lock);

	अगर (!list_empty(&list)) अणु
		rmcd_debug(EXIT, "temp list not empty");
		list_क्रम_each_entry_safe(req, req_next, &list, node) अणु
			rmcd_debug(EXIT, "free req->filp=%p cookie=%d compl=%s",
				   req->filp, req->cookie,
				   completion_करोne(&req->req_comp)?"yes":"no");
			list_del(&req->node);
			kref_put(&req->refcount, dma_req_मुक्त);
		पूर्ण
	पूर्ण

	put_dma_channel(priv);
	wret = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&priv->comp, पंचांगo);

	अगर (wret <= 0) अणु
		rmcd_error("%s(%d) failed waiting for DMA release err=%ld",
			current->comm, task_pid_nr(current), wret);
	पूर्ण

	अगर (priv->dmach != priv->md->dma_chan) अणु
		rmcd_debug(EXIT, "Release DMA channel for filp=%p %s(%d)",
			   filp, current->comm, task_pid_nr(current));
		rio_release_dma(priv->dmach);
	पूर्ण अन्यथा अणु
		rmcd_debug(EXIT, "Adjust default DMA channel refcount");
		kref_put(&md->dma_ref, mport_release_def_dma);
	पूर्ण

	priv->dmach = शून्य;
पूर्ण
#अन्यथा
#घोषणा mport_cdev_release_dma(priv) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * mport_cdev_release() - Release अक्षरacter device
 */
अटल पूर्णांक mport_cdev_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा mport_cdev_priv *priv = filp->निजी_data;
	काष्ठा mport_dev *chdev;
	काष्ठा rio_mport_pw_filter *pw_filter, *pw_filter_next;
	काष्ठा rio_mport_db_filter *db_filter, *db_filter_next;
	काष्ठा rio_mport_mapping *map, *_map;
	अचिन्हित दीर्घ flags;

	rmcd_debug(EXIT, "%s filp=%p", dev_name(&priv->md->dev), filp);

	chdev = priv->md;
	mport_cdev_release_dma(filp);

	priv->event_mask = 0;

	spin_lock_irqsave(&chdev->pw_lock, flags);
	अगर (!list_empty(&priv->pw_filters)) अणु
		list_क्रम_each_entry_safe(pw_filter, pw_filter_next,
					 &priv->pw_filters, priv_node)
			rio_mport_delete_pw_filter(pw_filter);
	पूर्ण
	spin_unlock_irqrestore(&chdev->pw_lock, flags);

	spin_lock_irqsave(&chdev->db_lock, flags);
	list_क्रम_each_entry_safe(db_filter, db_filter_next,
				 &priv->db_filters, priv_node) अणु
		rio_mport_delete_db_filter(db_filter);
	पूर्ण
	spin_unlock_irqrestore(&chdev->db_lock, flags);

	kfअगरo_मुक्त(&priv->event_fअगरo);

	mutex_lock(&chdev->buf_mutex);
	list_क्रम_each_entry_safe(map, _map, &chdev->mappings, node) अणु
		अगर (map->filp == filp) अणु
			rmcd_debug(EXIT, "release mapping %p filp=%p",
				   map->virt_addr, filp);
			kref_put(&map->ref, mport_release_mapping);
		पूर्ण
	पूर्ण
	mutex_unlock(&chdev->buf_mutex);

	mport_cdev_fasync(-1, filp, 0);
	filp->निजी_data = शून्य;
	mutex_lock(&chdev->file_mutex);
	list_del(&priv->list);
	mutex_unlock(&chdev->file_mutex);
	put_device(&chdev->dev);
	kमुक्त(priv);
	वापस 0;
पूर्ण

/*
 * mport_cdev_ioctl() - IOCTLs क्रम अक्षरacter device
 */
अटल दीर्घ mport_cdev_ioctl(काष्ठा file *filp,
		अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक err = -EINVAL;
	काष्ठा mport_cdev_priv *data = filp->निजी_data;
	काष्ठा mport_dev *md = data->md;

	अगर (atomic_पढ़ो(&md->active) == 0)
		वापस -ENODEV;

	चयन (cmd) अणु
	हाल RIO_MPORT_MAINT_READ_LOCAL:
		वापस rio_mport_मुख्यt_rd(data, (व्योम __user *)arg, 1);
	हाल RIO_MPORT_MAINT_WRITE_LOCAL:
		वापस rio_mport_मुख्यt_wr(data, (व्योम __user *)arg, 1);
	हाल RIO_MPORT_MAINT_READ_REMOTE:
		वापस rio_mport_मुख्यt_rd(data, (व्योम __user *)arg, 0);
	हाल RIO_MPORT_MAINT_WRITE_REMOTE:
		वापस rio_mport_मुख्यt_wr(data, (व्योम __user *)arg, 0);
	हाल RIO_MPORT_MAINT_HDID_SET:
		वापस मुख्यt_hdid_set(data, (व्योम __user *)arg);
	हाल RIO_MPORT_MAINT_COMPTAG_SET:
		वापस मुख्यt_comptag_set(data, (व्योम __user *)arg);
	हाल RIO_MPORT_MAINT_PORT_IDX_GET:
		वापस मुख्यt_port_idx_get(data, (व्योम __user *)arg);
	हाल RIO_MPORT_GET_PROPERTIES:
		md->properties.hdid = md->mport->host_deviceid;
		अगर (copy_to_user((व्योम __user *)arg, &(md->properties),
				 माप(md->properties)))
			वापस -EFAULT;
		वापस 0;
	हाल RIO_ENABLE_DOORBELL_RANGE:
		वापस rio_mport_add_db_filter(data, (व्योम __user *)arg);
	हाल RIO_DISABLE_DOORBELL_RANGE:
		वापस rio_mport_हटाओ_db_filter(data, (व्योम __user *)arg);
	हाल RIO_ENABLE_PORTWRITE_RANGE:
		वापस rio_mport_add_pw_filter(data, (व्योम __user *)arg);
	हाल RIO_DISABLE_PORTWRITE_RANGE:
		वापस rio_mport_हटाओ_pw_filter(data, (व्योम __user *)arg);
	हाल RIO_SET_EVENT_MASK:
		data->event_mask = (u32)arg;
		वापस 0;
	हाल RIO_GET_EVENT_MASK:
		अगर (copy_to_user((व्योम __user *)arg, &data->event_mask,
				    माप(u32)))
			वापस -EFAULT;
		वापस 0;
	हाल RIO_MAP_OUTBOUND:
		वापस rio_mport_obw_map(filp, (व्योम __user *)arg);
	हाल RIO_MAP_INBOUND:
		वापस rio_mport_map_inbound(filp, (व्योम __user *)arg);
	हाल RIO_UNMAP_OUTBOUND:
		वापस rio_mport_obw_मुक्त(filp, (व्योम __user *)arg);
	हाल RIO_UNMAP_INBOUND:
		वापस rio_mport_inbound_मुक्त(filp, (व्योम __user *)arg);
	हाल RIO_ALLOC_DMA:
		वापस rio_mport_alloc_dma(filp, (व्योम __user *)arg);
	हाल RIO_FREE_DMA:
		वापस rio_mport_मुक्त_dma(filp, (व्योम __user *)arg);
	हाल RIO_WAIT_FOR_ASYNC:
		वापस rio_mport_रुको_क्रम_async_dma(filp, (व्योम __user *)arg);
	हाल RIO_TRANSFER:
		वापस rio_mport_transfer_ioctl(filp, (व्योम __user *)arg);
	हाल RIO_DEV_ADD:
		वापस rio_mport_add_riodev(data, (व्योम __user *)arg);
	हाल RIO_DEV_DEL:
		वापस rio_mport_del_riodev(data, (व्योम __user *)arg);
	शेष:
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

/*
 * mport_release_mapping - मुक्त mapping resources and info काष्ठाure
 * @ref: a poपूर्णांकer to the kref within काष्ठा rio_mport_mapping
 *
 * NOTE: Shall be called जबतक holding buf_mutex.
 */
अटल व्योम mport_release_mapping(काष्ठा kref *ref)
अणु
	काष्ठा rio_mport_mapping *map =
			container_of(ref, काष्ठा rio_mport_mapping, ref);
	काष्ठा rio_mport *mport = map->md->mport;

	rmcd_debug(MMAP, "type %d mapping @ %p (phys = %pad) for %s",
		   map->dir, map->virt_addr,
		   &map->phys_addr, mport->name);

	list_del(&map->node);

	चयन (map->dir) अणु
	हाल MAP_INBOUND:
		rio_unmap_inb_region(mport, map->phys_addr);
		fallthrough;
	हाल MAP_DMA:
		dma_मुक्त_coherent(mport->dev.parent, map->size,
				  map->virt_addr, map->phys_addr);
		अवरोध;
	हाल MAP_OUTBOUND:
		rio_unmap_outb_region(mport, map->rioid, map->rio_addr);
		अवरोध;
	पूर्ण
	kमुक्त(map);
पूर्ण

अटल व्योम mport_mm_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा rio_mport_mapping *map = vma->vm_निजी_data;

	rmcd_debug(MMAP, "%pad", &map->phys_addr);
	kref_get(&map->ref);
पूर्ण

अटल व्योम mport_mm_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा rio_mport_mapping *map = vma->vm_निजी_data;

	rmcd_debug(MMAP, "%pad", &map->phys_addr);
	mutex_lock(&map->md->buf_mutex);
	kref_put(&map->ref, mport_release_mapping);
	mutex_unlock(&map->md->buf_mutex);
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा vm_ops = अणु
	.खोलो =	mport_mm_खोलो,
	.बंद = mport_mm_बंद,
पूर्ण;

अटल पूर्णांक mport_cdev_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा mport_cdev_priv *priv = filp->निजी_data;
	काष्ठा mport_dev *md;
	माप_प्रकार size = vma->vm_end - vma->vm_start;
	dma_addr_t baddr;
	अचिन्हित दीर्घ offset;
	पूर्णांक found = 0, ret;
	काष्ठा rio_mport_mapping *map;

	rmcd_debug(MMAP, "0x%x bytes at offset 0x%lx",
		   (अचिन्हित पूर्णांक)size, vma->vm_pgoff);

	md = priv->md;
	baddr = ((dma_addr_t)vma->vm_pgoff << PAGE_SHIFT);

	mutex_lock(&md->buf_mutex);
	list_क्रम_each_entry(map, &md->mappings, node) अणु
		अगर (baddr >= map->phys_addr &&
		    baddr < (map->phys_addr + map->size)) अणु
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&md->buf_mutex);

	अगर (!found)
		वापस -ENOMEM;

	offset = baddr - map->phys_addr;

	अगर (size + offset > map->size)
		वापस -EINVAL;

	vma->vm_pgoff = offset >> PAGE_SHIFT;
	rmcd_debug(MMAP, "MMAP adjusted offset = 0x%lx", vma->vm_pgoff);

	अगर (map->dir == MAP_INBOUND || map->dir == MAP_DMA)
		ret = dma_mmap_coherent(md->mport->dev.parent, vma,
				map->virt_addr, map->phys_addr, map->size);
	अन्यथा अगर (map->dir == MAP_OUTBOUND) अणु
		vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
		ret = vm_iomap_memory(vma, map->phys_addr, map->size);
	पूर्ण अन्यथा अणु
		rmcd_error("Attempt to mmap unsupported mapping type");
		ret = -EIO;
	पूर्ण

	अगर (!ret) अणु
		vma->vm_निजी_data = map;
		vma->vm_ops = &vm_ops;
		mport_mm_खोलो(vma);
	पूर्ण अन्यथा अणु
		rmcd_error("MMAP exit with err=%d", ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल __poll_t mport_cdev_poll(काष्ठा file *filp, poll_table *रुको)
अणु
	काष्ठा mport_cdev_priv *priv = filp->निजी_data;

	poll_रुको(filp, &priv->event_rx_रुको, रुको);
	अगर (kfअगरo_len(&priv->event_fअगरo))
		वापस EPOLLIN | EPOLLRDNORM;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार mport_पढ़ो(काष्ठा file *filp, अक्षर __user *buf, माप_प्रकार count,
			loff_t *ppos)
अणु
	काष्ठा mport_cdev_priv *priv = filp->निजी_data;
	पूर्णांक copied;
	sमाप_प्रकार ret;

	अगर (!count)
		वापस 0;

	अगर (kfअगरo_is_empty(&priv->event_fअगरo) &&
	    (filp->f_flags & O_NONBLOCK))
		वापस -EAGAIN;

	अगर (count % माप(काष्ठा rio_event))
		वापस -EINVAL;

	ret = रुको_event_पूर्णांकerruptible(priv->event_rx_रुको,
					kfअगरo_len(&priv->event_fअगरo) != 0);
	अगर (ret)
		वापस ret;

	जबतक (ret < count) अणु
		अगर (kfअगरo_to_user(&priv->event_fअगरo, buf,
		      माप(काष्ठा rio_event), &copied))
			वापस -EFAULT;
		ret += copied;
		buf += copied;
	पूर्ण

	वापस ret;
पूर्ण

अटल sमाप_प्रकार mport_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
			 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा mport_cdev_priv *priv = filp->निजी_data;
	काष्ठा rio_mport *mport = priv->md->mport;
	काष्ठा rio_event event;
	पूर्णांक len, ret;

	अगर (!count)
		वापस 0;

	अगर (count % माप(event))
		वापस -EINVAL;

	len = 0;
	जबतक ((count - len) >= (पूर्णांक)माप(event)) अणु
		अगर (copy_from_user(&event, buf, माप(event)))
			वापस -EFAULT;

		अगर (event.header != RIO_DOORBELL)
			वापस -EINVAL;

		ret = rio_mport_send_करोorbell(mport,
					      event.u.करोorbell.rioid,
					      event.u.करोorbell.payload);
		अगर (ret < 0)
			वापस ret;

		len += माप(event);
		buf += माप(event);
	पूर्ण

	वापस len;
पूर्ण

अटल स्थिर काष्ठा file_operations mport_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= mport_cdev_खोलो,
	.release	= mport_cdev_release,
	.poll		= mport_cdev_poll,
	.पढ़ो		= mport_पढ़ो,
	.ग_लिखो		= mport_ग_लिखो,
	.mmap		= mport_cdev_mmap,
	.fasync		= mport_cdev_fasync,
	.unlocked_ioctl = mport_cdev_ioctl
पूर्ण;

/*
 * Character device management
 */

अटल व्योम mport_device_release(काष्ठा device *dev)
अणु
	काष्ठा mport_dev *md;

	rmcd_debug(EXIT, "%s", dev_name(dev));
	md = container_of(dev, काष्ठा mport_dev, dev);
	kमुक्त(md);
पूर्ण

/*
 * mport_cdev_add() - Create mport_dev from rio_mport
 * @mport:	RapidIO master port
 */
अटल काष्ठा mport_dev *mport_cdev_add(काष्ठा rio_mport *mport)
अणु
	पूर्णांक ret = 0;
	काष्ठा mport_dev *md;
	काष्ठा rio_mport_attr attr;

	md = kzalloc(माप(*md), GFP_KERNEL);
	अगर (!md) अणु
		rmcd_error("Unable allocate a device object");
		वापस शून्य;
	पूर्ण

	md->mport = mport;
	mutex_init(&md->buf_mutex);
	mutex_init(&md->file_mutex);
	INIT_LIST_HEAD(&md->file_list);

	device_initialize(&md->dev);
	md->dev.devt = MKDEV(MAJOR(dev_number), mport->id);
	md->dev.class = dev_class;
	md->dev.parent = &mport->dev;
	md->dev.release = mport_device_release;
	dev_set_name(&md->dev, DEV_NAME "%d", mport->id);
	atomic_set(&md->active, 1);

	cdev_init(&md->cdev, &mport_fops);
	md->cdev.owner = THIS_MODULE;

	INIT_LIST_HEAD(&md->करोorbells);
	spin_lock_init(&md->db_lock);
	INIT_LIST_HEAD(&md->portग_लिखोs);
	spin_lock_init(&md->pw_lock);
	INIT_LIST_HEAD(&md->mappings);

	md->properties.id = mport->id;
	md->properties.sys_size = mport->sys_size;
	md->properties.hdid = mport->host_deviceid;
	md->properties.index = mport->index;

	/* The transfer_mode property will be वापसed through mport query
	 * पूर्णांकerface
	 */
#अगर_घोषित CONFIG_FSL_RIO /* क्रम now: only on Freescale's SoCs */
	md->properties.transfer_mode |= RIO_TRANSFER_MODE_MAPPED;
#अन्यथा
	md->properties.transfer_mode |= RIO_TRANSFER_MODE_TRANSFER;
#पूर्ण_अगर

	ret = cdev_device_add(&md->cdev, &md->dev);
	अगर (ret) अणु
		rmcd_error("Failed to register mport %d (err=%d)",
		       mport->id, ret);
		जाओ err_cdev;
	पूर्ण
	ret = rio_query_mport(mport, &attr);
	अगर (!ret) अणु
		md->properties.flags = attr.flags;
		md->properties.link_speed = attr.link_speed;
		md->properties.link_width = attr.link_width;
		md->properties.dma_max_sge = attr.dma_max_sge;
		md->properties.dma_max_size = attr.dma_max_size;
		md->properties.dma_align = attr.dma_align;
		md->properties.cap_sys_size = 0;
		md->properties.cap_transfer_mode = 0;
		md->properties.cap_addr_size = 0;
	पूर्ण अन्यथा
		pr_info(DRV_PREFIX "Failed to obtain info for %s cdev(%d:%d)\n",
			mport->name, MAJOR(dev_number), mport->id);

	mutex_lock(&mport_devs_lock);
	list_add_tail(&md->node, &mport_devs);
	mutex_unlock(&mport_devs_lock);

	pr_info(DRV_PREFIX "Added %s cdev(%d:%d)\n",
		mport->name, MAJOR(dev_number), mport->id);

	वापस md;

err_cdev:
	put_device(&md->dev);
	वापस शून्य;
पूर्ण

/*
 * mport_cdev_terminate_dma() - Stop all active DMA data transfers and release
 *                              associated DMA channels.
 */
अटल व्योम mport_cdev_terminate_dma(काष्ठा mport_dev *md)
अणु
#अगर_घोषित CONFIG_RAPIDIO_DMA_ENGINE
	काष्ठा mport_cdev_priv *client;

	rmcd_debug(DMA, "%s", dev_name(&md->dev));

	mutex_lock(&md->file_mutex);
	list_क्रम_each_entry(client, &md->file_list, list) अणु
		अगर (client->dmach) अणु
			dmaengine_terminate_all(client->dmach);
			rio_release_dma(client->dmach);
		पूर्ण
	पूर्ण
	mutex_unlock(&md->file_mutex);

	अगर (md->dma_chan) अणु
		dmaengine_terminate_all(md->dma_chan);
		rio_release_dma(md->dma_chan);
		md->dma_chan = शून्य;
	पूर्ण
#पूर्ण_अगर
पूर्ण


/*
 * mport_cdev_समाप्त_fasync() - Send SIGIO संकेत to all processes with खोलो
 *                            mport_cdev files.
 */
अटल पूर्णांक mport_cdev_समाप्त_fasync(काष्ठा mport_dev *md)
अणु
	अचिन्हित पूर्णांक files = 0;
	काष्ठा mport_cdev_priv *client;

	mutex_lock(&md->file_mutex);
	list_क्रम_each_entry(client, &md->file_list, list) अणु
		अगर (client->async_queue)
			समाप्त_fasync(&client->async_queue, SIGIO, POLL_HUP);
		files++;
	पूर्ण
	mutex_unlock(&md->file_mutex);
	वापस files;
पूर्ण

/*
 * mport_cdev_हटाओ() - Remove mport अक्षरacter device
 * @dev:	Mport device to हटाओ
 */
अटल व्योम mport_cdev_हटाओ(काष्ठा mport_dev *md)
अणु
	काष्ठा rio_mport_mapping *map, *_map;

	rmcd_debug(EXIT, "Remove %s cdev", md->mport->name);
	atomic_set(&md->active, 0);
	mport_cdev_terminate_dma(md);
	rio_del_mport_pw_handler(md->mport, md, rio_mport_pw_handler);
	cdev_device_del(&md->cdev, &md->dev);
	mport_cdev_समाप्त_fasync(md);

	/* TODO: करो we need to give clients some समय to बंद file
	 * descriptors? Simple रुको क्रम XX, or kref?
	 */

	/*
	 * Release DMA buffers allocated क्रम the mport device.
	 * Disable associated inbound Rapidio requests mapping अगर applicable.
	 */
	mutex_lock(&md->buf_mutex);
	list_क्रम_each_entry_safe(map, _map, &md->mappings, node) अणु
		kref_put(&map->ref, mport_release_mapping);
	पूर्ण
	mutex_unlock(&md->buf_mutex);

	अगर (!list_empty(&md->mappings))
		rmcd_warn("WARNING: %s pending mappings on removal",
			  md->mport->name);

	rio_release_inb_dbell(md->mport, 0, 0x0fff);

	put_device(&md->dev);
पूर्ण

/*
 * RIO rio_mport_पूर्णांकerface driver
 */

/*
 * mport_add_mport() - Add rio_mport from LDM device काष्ठा
 * @dev:		Linux device model काष्ठा
 * @class_पूर्णांकf:	Linux class_पूर्णांकerface
 */
अटल पूर्णांक mport_add_mport(काष्ठा device *dev,
		काष्ठा class_पूर्णांकerface *class_पूर्णांकf)
अणु
	काष्ठा rio_mport *mport = शून्य;
	काष्ठा mport_dev *chdev = शून्य;

	mport = to_rio_mport(dev);
	अगर (!mport)
		वापस -ENODEV;

	chdev = mport_cdev_add(mport);
	अगर (!chdev)
		वापस -ENODEV;

	वापस 0;
पूर्ण

/*
 * mport_हटाओ_mport() - Remove rio_mport from global list
 * TODO हटाओ device from global mport_dev list
 */
अटल व्योम mport_हटाओ_mport(काष्ठा device *dev,
		काष्ठा class_पूर्णांकerface *class_पूर्णांकf)
अणु
	काष्ठा rio_mport *mport = शून्य;
	काष्ठा mport_dev *chdev;
	पूर्णांक found = 0;

	mport = to_rio_mport(dev);
	rmcd_debug(EXIT, "Remove %s", mport->name);

	mutex_lock(&mport_devs_lock);
	list_क्रम_each_entry(chdev, &mport_devs, node) अणु
		अगर (chdev->mport->id == mport->id) अणु
			atomic_set(&chdev->active, 0);
			list_del(&chdev->node);
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&mport_devs_lock);

	अगर (found)
		mport_cdev_हटाओ(chdev);
पूर्ण

/* the rio_mport_पूर्णांकerface is used to handle local mport devices */
अटल काष्ठा class_पूर्णांकerface rio_mport_पूर्णांकerface __refdata = अणु
	.class		= &rio_mport_class,
	.add_dev	= mport_add_mport,
	.हटाओ_dev	= mport_हटाओ_mport,
पूर्ण;

/*
 * Linux kernel module
 */

/*
 * mport_init - Driver module loading
 */
अटल पूर्णांक __init mport_init(व्योम)
अणु
	पूर्णांक ret;

	/* Create device class needed by udev */
	dev_class = class_create(THIS_MODULE, DRV_NAME);
	अगर (IS_ERR(dev_class)) अणु
		rmcd_error("Unable to create " DRV_NAME " class");
		वापस PTR_ERR(dev_class);
	पूर्ण

	ret = alloc_chrdev_region(&dev_number, 0, RIO_MAX_MPORTS, DRV_NAME);
	अगर (ret < 0)
		जाओ err_chr;

	rmcd_debug(INIT, "Registered class with major=%d", MAJOR(dev_number));

	/* Register to rio_mport_पूर्णांकerface */
	ret = class_पूर्णांकerface_रेजिस्टर(&rio_mport_पूर्णांकerface);
	अगर (ret) अणु
		rmcd_error("class_interface_register() failed, err=%d", ret);
		जाओ err_cli;
	पूर्ण

	वापस 0;

err_cli:
	unरेजिस्टर_chrdev_region(dev_number, RIO_MAX_MPORTS);
err_chr:
	class_destroy(dev_class);
	वापस ret;
पूर्ण

/**
 * mport_निकास - Driver module unloading
 */
अटल व्योम __निकास mport_निकास(व्योम)
अणु
	class_पूर्णांकerface_unरेजिस्टर(&rio_mport_पूर्णांकerface);
	class_destroy(dev_class);
	unरेजिस्टर_chrdev_region(dev_number, RIO_MAX_MPORTS);
पूर्ण

module_init(mport_init);
module_निकास(mport_निकास);

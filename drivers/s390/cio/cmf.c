<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Linux on zSeries Channel Measurement Facility support
 *
 * Copyright IBM Corp. 2000, 2006
 *
 * Authors: Arnd Bergmann <arndb@de.ibm.com>
 *	    Cornelia Huck <cornelia.huck@de.ibm.com>
 *
 * original idea from Natarajan Krishnaswami <nkrishna@us.ibm.com>
 */

#घोषणा KMSG_COMPONENT "cio"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/memblock.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/export.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयx.h>	/* get_tod_घड़ी() */

#समावेश <यंत्र/ccwdev.h>
#समावेश <यंत्र/cपन.स>
#समावेश <यंत्र/cmb.h>
#समावेश <यंत्र/भाग64.h>

#समावेश "cio.h"
#समावेश "css.h"
#समावेश "device.h"
#समावेश "ioasm.h"
#समावेश "chsc.h"

/*
 * parameter to enable cmf during boot, possible uses are:
 *  "s390cmf" -- enable cmf and allocate 2 MB of ram so measuring can be
 *               used on any subchannel
 *  "s390cmf=<num>" -- enable cmf and allocate enough memory to measure
 *                     <num> subchannel, where <num> is an पूर्णांकeger
 *                     between 1 and 65535, शेष is 1024
 */
#घोषणा ARGSTRING "s390cmf"

/* indices क्रम READCMB */
क्रमागत cmb_index अणु
	avg_utilization = -1,
 /* basic and exended क्रमmat: */
	cmb_ssch_rsch_count = 0,
	cmb_sample_count,
	cmb_device_connect_समय,
	cmb_function_pending_समय,
	cmb_device_disconnect_समय,
	cmb_control_unit_queuing_समय,
	cmb_device_active_only_समय,
 /* extended क्रमmat only: */
	cmb_device_busy_समय,
	cmb_initial_command_response_समय,
पूर्ण;

/**
 * क्रमागत cmb_क्रमmat - types of supported measurement block क्रमmats
 *
 * @CMF_BASIC:      traditional channel measurement blocks supported
 *		    by all machines that we run on
 * @CMF_EXTENDED:   improved क्रमmat that was पूर्णांकroduced with the z990
 *		    machine
 * @CMF_AUTODETECT: शेष: use extended क्रमmat when running on a machine
 *		    supporting extended क्रमmat, otherwise fall back to
 *		    basic क्रमmat
 */
क्रमागत cmb_क्रमmat अणु
	CMF_BASIC,
	CMF_EXTENDED,
	CMF_AUTODETECT = -1,
पूर्ण;

/*
 * क्रमmat - actual क्रमmat क्रम all measurement blocks
 *
 * The क्रमmat module parameter can be set to a value of 0 (zero)
 * or 1, indicating basic or extended क्रमmat as described क्रम
 * क्रमागत cmb_क्रमmat.
 */
अटल पूर्णांक क्रमmat = CMF_AUTODETECT;
module_param(क्रमmat, bपूर्णांक, 0444);

/**
 * काष्ठा cmb_operations - functions to use depending on cmb_क्रमmat
 *
 * Most of these functions operate on a काष्ठा ccw_device. There is only
 * one instance of काष्ठा cmb_operations because the क्रमmat of the measurement
 * data is guaranteed to be the same क्रम every ccw_device.
 *
 * @alloc:	allocate memory क्रम a channel measurement block,
 *		either with the help of a special pool or with kदो_स्मृति
 * @मुक्त:	मुक्त memory allocated with @alloc
 * @set:	enable or disable measurement
 * @पढ़ो:	पढ़ो a measurement entry at an index
 * @पढ़ोall:	पढ़ो a measurement block in a common क्रमmat
 * @reset:	clear the data in the associated measurement block and
 *		reset its समय stamp
 */
काष्ठा cmb_operations अणु
	पूर्णांक  (*alloc)  (काष्ठा ccw_device *);
	व्योम (*मुक्त)   (काष्ठा ccw_device *);
	पूर्णांक  (*set)    (काष्ठा ccw_device *, u32);
	u64  (*पढ़ो)   (काष्ठा ccw_device *, पूर्णांक);
	पूर्णांक  (*पढ़ोall)(काष्ठा ccw_device *, काष्ठा cmbdata *);
	व्योम (*reset)  (काष्ठा ccw_device *);
/* निजी: */
	काष्ठा attribute_group *attr_group;
पूर्ण;
अटल काष्ठा cmb_operations *cmbops;

काष्ठा cmb_data अणु
	व्योम *hw_block;   /* Poपूर्णांकer to block updated by hardware */
	व्योम *last_block; /* Last changed block copied from hardware block */
	पूर्णांक size;	  /* Size of hw_block and last_block */
	अचिन्हित दीर्घ दीर्घ last_update;  /* when last_block was updated */
पूर्ण;

/*
 * Our user पूर्णांकerface is deचिन्हित in terms of nanoseconds,
 * जबतक the hardware measures total बार in its own
 * unit.
 */
अटल अंतरभूत u64 समय_प्रकारo_nsec(u32 value)
अणु
	वापस ((u64)value) * 128000ull;
पूर्ण

/*
 * Users are usually पूर्णांकerested in average बार,
 * not accumulated समय.
 * This also helps us with atomicity problems
 * when पढ़ोing sinlge values.
 */
अटल अंतरभूत u64 समय_प्रकारo_avg_nsec(u32 value, u32 count)
अणु
	u64 ret;

	/* no samples yet, aव्योम भागision by 0 */
	अगर (count == 0)
		वापस 0;

	/* value comes in units of 128 तगsec */
	ret = समय_प्रकारo_nsec(value);
	करो_भाग(ret, count);

	वापस ret;
पूर्ण

#घोषणा CMF_OFF 0
#घोषणा CMF_ON	2

/*
 * Activate or deactivate the channel monitor. When area is शून्य,
 * the monitor is deactivated. The channel monitor needs to
 * be active in order to measure subchannels, which also need
 * to be enabled.
 */
अटल अंतरभूत व्योम cmf_activate(व्योम *area, अचिन्हित पूर्णांक onoff)
अणु
	रेजिस्टर व्योम * __gpr2 यंत्र("2");
	रेजिस्टर दीर्घ __gpr1 यंत्र("1");

	__gpr2 = area;
	__gpr1 = onoff;
	/* activate channel measurement */
	यंत्र("schm" : : "d" (__gpr2), "d" (__gpr1) );
पूर्ण

अटल पूर्णांक set_schib(काष्ठा ccw_device *cdev, u32 mme, पूर्णांक mbfc,
		     अचिन्हित दीर्घ address)
अणु
	काष्ठा subchannel *sch = to_subchannel(cdev->dev.parent);
	पूर्णांक ret;

	sch->config.mme = mme;
	sch->config.mbfc = mbfc;
	/* address can be either a block address or a block index */
	अगर (mbfc)
		sch->config.mba = address;
	अन्यथा
		sch->config.mbi = address;

	ret = cio_commit_config(sch);
	अगर (!mme && ret == -ENODEV) अणु
		/*
		 * The task was to disable measurement block updates but
		 * the subchannel is alपढ़ोy gone. Report success.
		 */
		ret = 0;
	पूर्ण
	वापस ret;
पूर्ण

काष्ठा set_schib_काष्ठा अणु
	u32 mme;
	पूर्णांक mbfc;
	अचिन्हित दीर्घ address;
	रुको_queue_head_t रुको;
	पूर्णांक ret;
पूर्ण;

#घोषणा CMF_PENDING 1
#घोषणा SET_SCHIB_TIMEOUT (10 * HZ)

अटल पूर्णांक set_schib_रुको(काष्ठा ccw_device *cdev, u32 mme,
			  पूर्णांक mbfc, अचिन्हित दीर्घ address)
अणु
	काष्ठा set_schib_काष्ठा set_data;
	पूर्णांक ret = -ENODEV;

	spin_lock_irq(cdev->ccwlock);
	अगर (!cdev->निजी->cmb)
		जाओ out;

	ret = set_schib(cdev, mme, mbfc, address);
	अगर (ret != -EBUSY)
		जाओ out;

	/* अगर the device is not online, करोn't even try again */
	अगर (cdev->निजी->state != DEV_STATE_ONLINE)
		जाओ out;

	init_रुकोqueue_head(&set_data.रुको);
	set_data.mme = mme;
	set_data.mbfc = mbfc;
	set_data.address = address;
	set_data.ret = CMF_PENDING;

	cdev->निजी->state = DEV_STATE_CMFCHANGE;
	cdev->निजी->cmb_रुको = &set_data;
	spin_unlock_irq(cdev->ccwlock);

	ret = रुको_event_पूर्णांकerruptible_समयout(set_data.रुको,
					       set_data.ret != CMF_PENDING,
					       SET_SCHIB_TIMEOUT);
	spin_lock_irq(cdev->ccwlock);
	अगर (ret <= 0) अणु
		अगर (set_data.ret == CMF_PENDING) अणु
			set_data.ret = (ret == 0) ? -ETIME : ret;
			अगर (cdev->निजी->state == DEV_STATE_CMFCHANGE)
				cdev->निजी->state = DEV_STATE_ONLINE;
		पूर्ण
	पूर्ण
	cdev->निजी->cmb_रुको = शून्य;
	ret = set_data.ret;
out:
	spin_unlock_irq(cdev->ccwlock);
	वापस ret;
पूर्ण

व्योम retry_set_schib(काष्ठा ccw_device *cdev)
अणु
	काष्ठा set_schib_काष्ठा *set_data = cdev->निजी->cmb_रुको;

	अगर (!set_data)
		वापस;

	set_data->ret = set_schib(cdev, set_data->mme, set_data->mbfc,
				  set_data->address);
	wake_up(&set_data->रुको);
पूर्ण

अटल पूर्णांक cmf_copy_block(काष्ठा ccw_device *cdev)
अणु
	काष्ठा subchannel *sch = to_subchannel(cdev->dev.parent);
	काष्ठा cmb_data *cmb_data;
	व्योम *hw_block;

	अगर (cio_update_schib(sch))
		वापस -ENODEV;

	अगर (scsw_fctl(&sch->schib.scsw) & SCSW_FCTL_START_FUNC) अणु
		/* Don't copy अगर a start function is in progress. */
		अगर ((!(scsw_actl(&sch->schib.scsw) & SCSW_ACTL_SUSPENDED)) &&
		    (scsw_actl(&sch->schib.scsw) &
		     (SCSW_ACTL_DEVACT | SCSW_ACTL_SCHACT)) &&
		    (!(scsw_stctl(&sch->schib.scsw) & SCSW_STCTL_SEC_STATUS)))
			वापस -EBUSY;
	पूर्ण
	cmb_data = cdev->निजी->cmb;
	hw_block = cmb_data->hw_block;
	स_नकल(cmb_data->last_block, hw_block, cmb_data->size);
	cmb_data->last_update = get_tod_घड़ी();
	वापस 0;
पूर्ण

काष्ठा copy_block_काष्ठा अणु
	रुको_queue_head_t रुको;
	पूर्णांक ret;
पूर्ण;

अटल पूर्णांक cmf_cmb_copy_रुको(काष्ठा ccw_device *cdev)
अणु
	काष्ठा copy_block_काष्ठा copy_block;
	पूर्णांक ret = -ENODEV;

	spin_lock_irq(cdev->ccwlock);
	अगर (!cdev->निजी->cmb)
		जाओ out;

	ret = cmf_copy_block(cdev);
	अगर (ret != -EBUSY)
		जाओ out;

	अगर (cdev->निजी->state != DEV_STATE_ONLINE)
		जाओ out;

	init_रुकोqueue_head(&copy_block.रुको);
	copy_block.ret = CMF_PENDING;

	cdev->निजी->state = DEV_STATE_CMFUPDATE;
	cdev->निजी->cmb_रुको = &copy_block;
	spin_unlock_irq(cdev->ccwlock);

	ret = रुको_event_पूर्णांकerruptible(copy_block.रुको,
				       copy_block.ret != CMF_PENDING);
	spin_lock_irq(cdev->ccwlock);
	अगर (ret) अणु
		अगर (copy_block.ret == CMF_PENDING) अणु
			copy_block.ret = -ERESTARTSYS;
			अगर (cdev->निजी->state == DEV_STATE_CMFUPDATE)
				cdev->निजी->state = DEV_STATE_ONLINE;
		पूर्ण
	पूर्ण
	cdev->निजी->cmb_रुको = शून्य;
	ret = copy_block.ret;
out:
	spin_unlock_irq(cdev->ccwlock);
	वापस ret;
पूर्ण

व्योम cmf_retry_copy_block(काष्ठा ccw_device *cdev)
अणु
	काष्ठा copy_block_काष्ठा *copy_block = cdev->निजी->cmb_रुको;

	अगर (!copy_block)
		वापस;

	copy_block->ret = cmf_copy_block(cdev);
	wake_up(&copy_block->रुको);
पूर्ण

अटल व्योम cmf_generic_reset(काष्ठा ccw_device *cdev)
अणु
	काष्ठा cmb_data *cmb_data;

	spin_lock_irq(cdev->ccwlock);
	cmb_data = cdev->निजी->cmb;
	अगर (cmb_data) अणु
		स_रखो(cmb_data->last_block, 0, cmb_data->size);
		/*
		 * Need to reset hw block as well to make the hardware start
		 * from 0 again.
		 */
		स_रखो(cmb_data->hw_block, 0, cmb_data->size);
		cmb_data->last_update = 0;
	पूर्ण
	cdev->निजी->cmb_start_समय = get_tod_घड़ी();
	spin_unlock_irq(cdev->ccwlock);
पूर्ण

/**
 * काष्ठा cmb_area - container क्रम global cmb data
 *
 * @mem:	poपूर्णांकer to CMBs (only in basic measurement mode)
 * @list:	contains a linked list of all subchannels
 * @num_channels: number of channels to be measured
 * @lock:	protect concurrent access to @mem and @list
 */
काष्ठा cmb_area अणु
	काष्ठा cmb *mem;
	काष्ठा list_head list;
	पूर्णांक num_channels;
	spinlock_t lock;
पूर्ण;

अटल काष्ठा cmb_area cmb_area = अणु
	.lock = __SPIN_LOCK_UNLOCKED(cmb_area.lock),
	.list = LIST_HEAD_INIT(cmb_area.list),
	.num_channels  = 1024,
पूर्ण;

/* ****** old style CMB handling ********/

/*
 * Basic channel measurement blocks are allocated in one contiguous
 * block of memory, which can not be moved as दीर्घ as any channel
 * is active. Thereक्रमe, a maximum number of subchannels needs to
 * be defined somewhere. This is a module parameter, शेषing to
 * a reasonable value of 1024, or 32 kb of memory.
 * Current kernels करोn't allow kदो_स्मृति with more than 128kb, so the
 * maximum is 4096.
 */

module_param_named(maxchannels, cmb_area.num_channels, uपूर्णांक, 0444);

/**
 * काष्ठा cmb - basic channel measurement block
 * @ssch_rsch_count: number of ssch and rsch
 * @sample_count: number of samples
 * @device_connect_समय: समय of device connect
 * @function_pending_समय: समय of function pending
 * @device_disconnect_समय: समय of device disconnect
 * @control_unit_queuing_समय: समय of control unit queuing
 * @device_active_only_समय: समय of device active only
 * @reserved: unused in basic measurement mode
 *
 * The measurement block as used by the hardware. The fields are described
 * further in z/Architecture Principles of Operation, chapter 17.
 *
 * The cmb area made up from these blocks must be a contiguous array and may
 * not be पुनः_स्मृतिated or मुक्तd.
 * Only one cmb area can be present in the प्रणाली.
 */
काष्ठा cmb अणु
	u16 ssch_rsch_count;
	u16 sample_count;
	u32 device_connect_समय;
	u32 function_pending_समय;
	u32 device_disconnect_समय;
	u32 control_unit_queuing_समय;
	u32 device_active_only_समय;
	u32 reserved[2];
पूर्ण;

/*
 * Insert a single device पूर्णांकo the cmb_area list.
 * Called with cmb_area.lock held from alloc_cmb.
 */
अटल पूर्णांक alloc_cmb_single(काष्ठा ccw_device *cdev,
			    काष्ठा cmb_data *cmb_data)
अणु
	काष्ठा cmb *cmb;
	काष्ठा ccw_device_निजी *node;
	पूर्णांक ret;

	spin_lock_irq(cdev->ccwlock);
	अगर (!list_empty(&cdev->निजी->cmb_list)) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	/*
	 * Find first unused cmb in cmb_area.mem.
	 * This is a little tricky: cmb_area.list
	 * reमुख्यs sorted by ->cmb->hw_data poपूर्णांकers.
	 */
	cmb = cmb_area.mem;
	list_क्रम_each_entry(node, &cmb_area.list, cmb_list) अणु
		काष्ठा cmb_data *data;
		data = node->cmb;
		अगर ((काष्ठा cmb*)data->hw_block > cmb)
			अवरोध;
		cmb++;
	पूर्ण
	अगर (cmb - cmb_area.mem >= cmb_area.num_channels) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* insert new cmb */
	list_add_tail(&cdev->निजी->cmb_list, &node->cmb_list);
	cmb_data->hw_block = cmb;
	cdev->निजी->cmb = cmb_data;
	ret = 0;
out:
	spin_unlock_irq(cdev->ccwlock);
	वापस ret;
पूर्ण

अटल पूर्णांक alloc_cmb(काष्ठा ccw_device *cdev)
अणु
	पूर्णांक ret;
	काष्ठा cmb *mem;
	sमाप_प्रकार size;
	काष्ठा cmb_data *cmb_data;

	/* Allocate निजी cmb_data. */
	cmb_data = kzalloc(माप(काष्ठा cmb_data), GFP_KERNEL);
	अगर (!cmb_data)
		वापस -ENOMEM;

	cmb_data->last_block = kzalloc(माप(काष्ठा cmb), GFP_KERNEL);
	अगर (!cmb_data->last_block) अणु
		kमुक्त(cmb_data);
		वापस -ENOMEM;
	पूर्ण
	cmb_data->size = माप(काष्ठा cmb);
	spin_lock(&cmb_area.lock);

	अगर (!cmb_area.mem) अणु
		/* there is no user yet, so we need a new area */
		size = माप(काष्ठा cmb) * cmb_area.num_channels;
		WARN_ON(!list_empty(&cmb_area.list));

		spin_unlock(&cmb_area.lock);
		mem = (व्योम*)__get_मुक्त_pages(GFP_KERNEL | GFP_DMA,
				 get_order(size));
		spin_lock(&cmb_area.lock);

		अगर (cmb_area.mem) अणु
			/* ok, another thपढ़ो was faster */
			मुक्त_pages((अचिन्हित दीर्घ)mem, get_order(size));
		पूर्ण अन्यथा अगर (!mem) अणु
			/* no luck */
			ret = -ENOMEM;
			जाओ out;
		पूर्ण अन्यथा अणु
			/* everything ok */
			स_रखो(mem, 0, size);
			cmb_area.mem = mem;
			cmf_activate(cmb_area.mem, CMF_ON);
		पूर्ण
	पूर्ण

	/* करो the actual allocation */
	ret = alloc_cmb_single(cdev, cmb_data);
out:
	spin_unlock(&cmb_area.lock);
	अगर (ret) अणु
		kमुक्त(cmb_data->last_block);
		kमुक्त(cmb_data);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम मुक्त_cmb(काष्ठा ccw_device *cdev)
अणु
	काष्ठा ccw_device_निजी *priv;
	काष्ठा cmb_data *cmb_data;

	spin_lock(&cmb_area.lock);
	spin_lock_irq(cdev->ccwlock);

	priv = cdev->निजी;
	cmb_data = priv->cmb;
	priv->cmb = शून्य;
	अगर (cmb_data)
		kमुक्त(cmb_data->last_block);
	kमुक्त(cmb_data);
	list_del_init(&priv->cmb_list);

	अगर (list_empty(&cmb_area.list)) अणु
		sमाप_प्रकार size;
		size = माप(काष्ठा cmb) * cmb_area.num_channels;
		cmf_activate(शून्य, CMF_OFF);
		मुक्त_pages((अचिन्हित दीर्घ)cmb_area.mem, get_order(size));
		cmb_area.mem = शून्य;
	पूर्ण
	spin_unlock_irq(cdev->ccwlock);
	spin_unlock(&cmb_area.lock);
पूर्ण

अटल पूर्णांक set_cmb(काष्ठा ccw_device *cdev, u32 mme)
अणु
	u16 offset;
	काष्ठा cmb_data *cmb_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(cdev->ccwlock, flags);
	अगर (!cdev->निजी->cmb) अणु
		spin_unlock_irqrestore(cdev->ccwlock, flags);
		वापस -EINVAL;
	पूर्ण
	cmb_data = cdev->निजी->cmb;
	offset = mme ? (काष्ठा cmb *)cmb_data->hw_block - cmb_area.mem : 0;
	spin_unlock_irqrestore(cdev->ccwlock, flags);

	वापस set_schib_रुको(cdev, mme, 0, offset);
पूर्ण

/* calculate utilization in 0.1 percent units */
अटल u64 __cmb_utilization(u64 device_connect_समय, u64 function_pending_समय,
			     u64 device_disconnect_समय, u64 start_समय)
अणु
	u64 utilization, elapsed_समय;

	utilization = समय_प्रकारo_nsec(device_connect_समय +
				   function_pending_समय +
				   device_disconnect_समय);

	elapsed_समय = get_tod_घड़ी() - start_समय;
	elapsed_समय = tod_to_ns(elapsed_समय);
	elapsed_समय /= 1000;

	वापस elapsed_समय ? (utilization / elapsed_समय) : 0;
पूर्ण

अटल u64 पढ़ो_cmb(काष्ठा ccw_device *cdev, पूर्णांक index)
अणु
	काष्ठा cmb_data *cmb_data;
	अचिन्हित दीर्घ flags;
	काष्ठा cmb *cmb;
	u64 ret = 0;
	u32 val;

	spin_lock_irqsave(cdev->ccwlock, flags);
	cmb_data = cdev->निजी->cmb;
	अगर (!cmb_data)
		जाओ out;

	cmb = cmb_data->hw_block;
	चयन (index) अणु
	हाल avg_utilization:
		ret = __cmb_utilization(cmb->device_connect_समय,
					cmb->function_pending_समय,
					cmb->device_disconnect_समय,
					cdev->निजी->cmb_start_समय);
		जाओ out;
	हाल cmb_ssch_rsch_count:
		ret = cmb->ssch_rsch_count;
		जाओ out;
	हाल cmb_sample_count:
		ret = cmb->sample_count;
		जाओ out;
	हाल cmb_device_connect_समय:
		val = cmb->device_connect_समय;
		अवरोध;
	हाल cmb_function_pending_समय:
		val = cmb->function_pending_समय;
		अवरोध;
	हाल cmb_device_disconnect_समय:
		val = cmb->device_disconnect_समय;
		अवरोध;
	हाल cmb_control_unit_queuing_समय:
		val = cmb->control_unit_queuing_समय;
		अवरोध;
	हाल cmb_device_active_only_समय:
		val = cmb->device_active_only_समय;
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण
	ret = समय_प्रकारo_avg_nsec(val, cmb->sample_count);
out:
	spin_unlock_irqrestore(cdev->ccwlock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक पढ़ोall_cmb(काष्ठा ccw_device *cdev, काष्ठा cmbdata *data)
अणु
	काष्ठा cmb *cmb;
	काष्ठा cmb_data *cmb_data;
	u64 समय;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	ret = cmf_cmb_copy_रुको(cdev);
	अगर (ret < 0)
		वापस ret;
	spin_lock_irqsave(cdev->ccwlock, flags);
	cmb_data = cdev->निजी->cmb;
	अगर (!cmb_data) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण
	अगर (cmb_data->last_update == 0) अणु
		ret = -EAGAIN;
		जाओ out;
	पूर्ण
	cmb = cmb_data->last_block;
	समय = cmb_data->last_update - cdev->निजी->cmb_start_समय;

	स_रखो(data, 0, माप(काष्ठा cmbdata));

	/* we only know values beक्रमe device_busy_समय */
	data->size = दुरत्व(काष्ठा cmbdata, device_busy_समय);

	data->elapsed_समय = tod_to_ns(समय);

	/* copy data to new काष्ठाure */
	data->ssch_rsch_count = cmb->ssch_rsch_count;
	data->sample_count = cmb->sample_count;

	/* समय fields are converted to nanoseconds जबतक copying */
	data->device_connect_समय = समय_प्रकारo_nsec(cmb->device_connect_समय);
	data->function_pending_समय = समय_प्रकारo_nsec(cmb->function_pending_समय);
	data->device_disconnect_समय =
		समय_प्रकारo_nsec(cmb->device_disconnect_समय);
	data->control_unit_queuing_समय
		= समय_प्रकारo_nsec(cmb->control_unit_queuing_समय);
	data->device_active_only_समय
		= समय_प्रकारo_nsec(cmb->device_active_only_समय);
	ret = 0;
out:
	spin_unlock_irqrestore(cdev->ccwlock, flags);
	वापस ret;
पूर्ण

अटल व्योम reset_cmb(काष्ठा ccw_device *cdev)
अणु
	cmf_generic_reset(cdev);
पूर्ण

अटल पूर्णांक cmf_enabled(काष्ठा ccw_device *cdev)
अणु
	पूर्णांक enabled;

	spin_lock_irq(cdev->ccwlock);
	enabled = !!cdev->निजी->cmb;
	spin_unlock_irq(cdev->ccwlock);

	वापस enabled;
पूर्ण

अटल काष्ठा attribute_group cmf_attr_group;

अटल काष्ठा cmb_operations cmbops_basic = अणु
	.alloc	= alloc_cmb,
	.मुक्त	= मुक्त_cmb,
	.set	= set_cmb,
	.पढ़ो	= पढ़ो_cmb,
	.पढ़ोall    = पढ़ोall_cmb,
	.reset	    = reset_cmb,
	.attr_group = &cmf_attr_group,
पूर्ण;

/* ******** extended cmb handling ********/

/**
 * काष्ठा cmbe - extended channel measurement block
 * @ssch_rsch_count: number of ssch and rsch
 * @sample_count: number of samples
 * @device_connect_समय: समय of device connect
 * @function_pending_समय: समय of function pending
 * @device_disconnect_समय: समय of device disconnect
 * @control_unit_queuing_समय: समय of control unit queuing
 * @device_active_only_समय: समय of device active only
 * @device_busy_समय: समय of device busy
 * @initial_command_response_समय: initial command response समय
 * @reserved: unused
 *
 * The measurement block as used by the hardware. May be in any 64 bit physical
 * location.
 * The fields are described further in z/Architecture Principles of Operation,
 * third edition, chapter 17.
 */
काष्ठा cmbe अणु
	u32 ssch_rsch_count;
	u32 sample_count;
	u32 device_connect_समय;
	u32 function_pending_समय;
	u32 device_disconnect_समय;
	u32 control_unit_queuing_समय;
	u32 device_active_only_समय;
	u32 device_busy_समय;
	u32 initial_command_response_समय;
	u32 reserved[7];
पूर्ण __packed __aligned(64);

अटल काष्ठा kmem_cache *cmbe_cache;

अटल पूर्णांक alloc_cmbe(काष्ठा ccw_device *cdev)
अणु
	काष्ठा cmb_data *cmb_data;
	काष्ठा cmbe *cmbe;
	पूर्णांक ret = -ENOMEM;

	cmbe = kmem_cache_zalloc(cmbe_cache, GFP_KERNEL);
	अगर (!cmbe)
		वापस ret;

	cmb_data = kzalloc(माप(*cmb_data), GFP_KERNEL);
	अगर (!cmb_data)
		जाओ out_मुक्त;

	cmb_data->last_block = kzalloc(माप(काष्ठा cmbe), GFP_KERNEL);
	अगर (!cmb_data->last_block)
		जाओ out_मुक्त;

	cmb_data->size = माप(*cmbe);
	cmb_data->hw_block = cmbe;

	spin_lock(&cmb_area.lock);
	spin_lock_irq(cdev->ccwlock);
	अगर (cdev->निजी->cmb)
		जाओ out_unlock;

	cdev->निजी->cmb = cmb_data;

	/* activate global measurement अगर this is the first channel */
	अगर (list_empty(&cmb_area.list))
		cmf_activate(शून्य, CMF_ON);
	list_add_tail(&cdev->निजी->cmb_list, &cmb_area.list);

	spin_unlock_irq(cdev->ccwlock);
	spin_unlock(&cmb_area.lock);
	वापस 0;

out_unlock:
	spin_unlock_irq(cdev->ccwlock);
	spin_unlock(&cmb_area.lock);
	ret = -EBUSY;
out_मुक्त:
	अगर (cmb_data)
		kमुक्त(cmb_data->last_block);
	kमुक्त(cmb_data);
	kmem_cache_मुक्त(cmbe_cache, cmbe);

	वापस ret;
पूर्ण

अटल व्योम मुक्त_cmbe(काष्ठा ccw_device *cdev)
अणु
	काष्ठा cmb_data *cmb_data;

	spin_lock(&cmb_area.lock);
	spin_lock_irq(cdev->ccwlock);
	cmb_data = cdev->निजी->cmb;
	cdev->निजी->cmb = शून्य;
	अगर (cmb_data) अणु
		kमुक्त(cmb_data->last_block);
		kmem_cache_मुक्त(cmbe_cache, cmb_data->hw_block);
	पूर्ण
	kमुक्त(cmb_data);

	/* deactivate global measurement अगर this is the last channel */
	list_del_init(&cdev->निजी->cmb_list);
	अगर (list_empty(&cmb_area.list))
		cmf_activate(शून्य, CMF_OFF);
	spin_unlock_irq(cdev->ccwlock);
	spin_unlock(&cmb_area.lock);
पूर्ण

अटल पूर्णांक set_cmbe(काष्ठा ccw_device *cdev, u32 mme)
अणु
	अचिन्हित दीर्घ mba;
	काष्ठा cmb_data *cmb_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(cdev->ccwlock, flags);
	अगर (!cdev->निजी->cmb) अणु
		spin_unlock_irqrestore(cdev->ccwlock, flags);
		वापस -EINVAL;
	पूर्ण
	cmb_data = cdev->निजी->cmb;
	mba = mme ? (अचिन्हित दीर्घ) cmb_data->hw_block : 0;
	spin_unlock_irqrestore(cdev->ccwlock, flags);

	वापस set_schib_रुको(cdev, mme, 1, mba);
पूर्ण

अटल u64 पढ़ो_cmbe(काष्ठा ccw_device *cdev, पूर्णांक index)
अणु
	काष्ठा cmb_data *cmb_data;
	अचिन्हित दीर्घ flags;
	काष्ठा cmbe *cmb;
	u64 ret = 0;
	u32 val;

	spin_lock_irqsave(cdev->ccwlock, flags);
	cmb_data = cdev->निजी->cmb;
	अगर (!cmb_data)
		जाओ out;

	cmb = cmb_data->hw_block;
	चयन (index) अणु
	हाल avg_utilization:
		ret = __cmb_utilization(cmb->device_connect_समय,
					cmb->function_pending_समय,
					cmb->device_disconnect_समय,
					cdev->निजी->cmb_start_समय);
		जाओ out;
	हाल cmb_ssch_rsch_count:
		ret = cmb->ssch_rsch_count;
		जाओ out;
	हाल cmb_sample_count:
		ret = cmb->sample_count;
		जाओ out;
	हाल cmb_device_connect_समय:
		val = cmb->device_connect_समय;
		अवरोध;
	हाल cmb_function_pending_समय:
		val = cmb->function_pending_समय;
		अवरोध;
	हाल cmb_device_disconnect_समय:
		val = cmb->device_disconnect_समय;
		अवरोध;
	हाल cmb_control_unit_queuing_समय:
		val = cmb->control_unit_queuing_समय;
		अवरोध;
	हाल cmb_device_active_only_समय:
		val = cmb->device_active_only_समय;
		अवरोध;
	हाल cmb_device_busy_समय:
		val = cmb->device_busy_समय;
		अवरोध;
	हाल cmb_initial_command_response_समय:
		val = cmb->initial_command_response_समय;
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण
	ret = समय_प्रकारo_avg_nsec(val, cmb->sample_count);
out:
	spin_unlock_irqrestore(cdev->ccwlock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक पढ़ोall_cmbe(काष्ठा ccw_device *cdev, काष्ठा cmbdata *data)
अणु
	काष्ठा cmbe *cmb;
	काष्ठा cmb_data *cmb_data;
	u64 समय;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	ret = cmf_cmb_copy_रुको(cdev);
	अगर (ret < 0)
		वापस ret;
	spin_lock_irqsave(cdev->ccwlock, flags);
	cmb_data = cdev->निजी->cmb;
	अगर (!cmb_data) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण
	अगर (cmb_data->last_update == 0) अणु
		ret = -EAGAIN;
		जाओ out;
	पूर्ण
	समय = cmb_data->last_update - cdev->निजी->cmb_start_समय;

	स_रखो (data, 0, माप(काष्ठा cmbdata));

	/* we only know values beक्रमe device_busy_समय */
	data->size = दुरत्व(काष्ठा cmbdata, device_busy_समय);

	data->elapsed_समय = tod_to_ns(समय);

	cmb = cmb_data->last_block;
	/* copy data to new काष्ठाure */
	data->ssch_rsch_count = cmb->ssch_rsch_count;
	data->sample_count = cmb->sample_count;

	/* समय fields are converted to nanoseconds जबतक copying */
	data->device_connect_समय = समय_प्रकारo_nsec(cmb->device_connect_समय);
	data->function_pending_समय = समय_प्रकारo_nsec(cmb->function_pending_समय);
	data->device_disconnect_समय =
		समय_प्रकारo_nsec(cmb->device_disconnect_समय);
	data->control_unit_queuing_समय
		= समय_प्रकारo_nsec(cmb->control_unit_queuing_समय);
	data->device_active_only_समय
		= समय_प्रकारo_nsec(cmb->device_active_only_समय);
	data->device_busy_समय = समय_प्रकारo_nsec(cmb->device_busy_समय);
	data->initial_command_response_समय
		= समय_प्रकारo_nsec(cmb->initial_command_response_समय);

	ret = 0;
out:
	spin_unlock_irqrestore(cdev->ccwlock, flags);
	वापस ret;
पूर्ण

अटल व्योम reset_cmbe(काष्ठा ccw_device *cdev)
अणु
	cmf_generic_reset(cdev);
पूर्ण

अटल काष्ठा attribute_group cmf_attr_group_ext;

अटल काष्ठा cmb_operations cmbops_extended = अणु
	.alloc	    = alloc_cmbe,
	.मुक्त	    = मुक्त_cmbe,
	.set	    = set_cmbe,
	.पढ़ो	    = पढ़ो_cmbe,
	.पढ़ोall    = पढ़ोall_cmbe,
	.reset	    = reset_cmbe,
	.attr_group = &cmf_attr_group_ext,
पूर्ण;

अटल sमाप_प्रकार cmb_show_attr(काष्ठा device *dev, अक्षर *buf, क्रमागत cmb_index idx)
अणु
	वापस प्र_लिखो(buf, "%lld\n",
		(अचिन्हित दीर्घ दीर्घ) cmf_पढ़ो(to_ccwdev(dev), idx));
पूर्ण

अटल sमाप_प्रकार cmb_show_avg_sample_पूर्णांकerval(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    अक्षर *buf)
अणु
	काष्ठा ccw_device *cdev = to_ccwdev(dev);
	अचिन्हित दीर्घ count;
	दीर्घ पूर्णांकerval;

	count = cmf_पढ़ो(cdev, cmb_sample_count);
	spin_lock_irq(cdev->ccwlock);
	अगर (count) अणु
		पूर्णांकerval = get_tod_घड़ी() - cdev->निजी->cmb_start_समय;
		पूर्णांकerval = tod_to_ns(पूर्णांकerval);
		पूर्णांकerval /= count;
	पूर्ण अन्यथा
		पूर्णांकerval = -1;
	spin_unlock_irq(cdev->ccwlock);
	वापस प्र_लिखो(buf, "%ld\n", पूर्णांकerval);
पूर्ण

अटल sमाप_प्रकार cmb_show_avg_utilization(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	अचिन्हित दीर्घ u = cmf_पढ़ो(to_ccwdev(dev), avg_utilization);

	वापस प्र_लिखो(buf, "%02lu.%01lu%%\n", u / 10, u % 10);
पूर्ण

#घोषणा cmf_attr(name) \
अटल sमाप_प्रकार show_##name(काष्ठा device *dev, \
			   काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु वापस cmb_show_attr((dev), buf, cmb_##name); पूर्ण \
अटल DEVICE_ATTR(name, 0444, show_##name, शून्य);

#घोषणा cmf_attr_avg(name) \
अटल sमाप_प्रकार show_avg_##name(काष्ठा device *dev, \
			       काष्ठा device_attribute *attr, अक्षर *buf) \
अणु वापस cmb_show_attr((dev), buf, cmb_##name); पूर्ण \
अटल DEVICE_ATTR(avg_##name, 0444, show_avg_##name, शून्य);

cmf_attr(ssch_rsch_count);
cmf_attr(sample_count);
cmf_attr_avg(device_connect_समय);
cmf_attr_avg(function_pending_समय);
cmf_attr_avg(device_disconnect_समय);
cmf_attr_avg(control_unit_queuing_समय);
cmf_attr_avg(device_active_only_समय);
cmf_attr_avg(device_busy_समय);
cmf_attr_avg(initial_command_response_समय);

अटल DEVICE_ATTR(avg_sample_पूर्णांकerval, 0444, cmb_show_avg_sample_पूर्णांकerval,
		   शून्य);
अटल DEVICE_ATTR(avg_utilization, 0444, cmb_show_avg_utilization, शून्य);

अटल काष्ठा attribute *cmf_attributes[] = अणु
	&dev_attr_avg_sample_पूर्णांकerval.attr,
	&dev_attr_avg_utilization.attr,
	&dev_attr_ssch_rsch_count.attr,
	&dev_attr_sample_count.attr,
	&dev_attr_avg_device_connect_समय.attr,
	&dev_attr_avg_function_pending_समय.attr,
	&dev_attr_avg_device_disconnect_समय.attr,
	&dev_attr_avg_control_unit_queuing_समय.attr,
	&dev_attr_avg_device_active_only_समय.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group cmf_attr_group = अणु
	.name  = "cmf",
	.attrs = cmf_attributes,
पूर्ण;

अटल काष्ठा attribute *cmf_attributes_ext[] = अणु
	&dev_attr_avg_sample_पूर्णांकerval.attr,
	&dev_attr_avg_utilization.attr,
	&dev_attr_ssch_rsch_count.attr,
	&dev_attr_sample_count.attr,
	&dev_attr_avg_device_connect_समय.attr,
	&dev_attr_avg_function_pending_समय.attr,
	&dev_attr_avg_device_disconnect_समय.attr,
	&dev_attr_avg_control_unit_queuing_समय.attr,
	&dev_attr_avg_device_active_only_समय.attr,
	&dev_attr_avg_device_busy_समय.attr,
	&dev_attr_avg_initial_command_response_समय.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group cmf_attr_group_ext = अणु
	.name  = "cmf",
	.attrs = cmf_attributes_ext,
पूर्ण;

अटल sमाप_प्रकार cmb_enable_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       अक्षर *buf)
अणु
	काष्ठा ccw_device *cdev = to_ccwdev(dev);

	वापस प्र_लिखो(buf, "%d\n", cmf_enabled(cdev));
पूर्ण

अटल sमाप_प्रकार cmb_enable_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
				माप_प्रकार c)
अणु
	काष्ठा ccw_device *cdev = to_ccwdev(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 16, &val);
	अगर (ret)
		वापस ret;

	चयन (val) अणु
	हाल 0:
		ret = disable_cmf(cdev);
		अवरोध;
	हाल 1:
		ret = enable_cmf(cdev);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret ? ret : c;
पूर्ण
DEVICE_ATTR_RW(cmb_enable);

/**
 * enable_cmf() - चयन on the channel measurement क्रम a specअगरic device
 *  @cdev:	The ccw device to be enabled
 *
 *  Enable channel measurements क्रम @cdev. If this is called on a device
 *  क्रम which channel measurement is alपढ़ोy enabled a reset of the
 *  measurement data is triggered.
 *  Returns: %0 क्रम success or a negative error value.
 *  Context:
 *    non-atomic
 */
पूर्णांक enable_cmf(काष्ठा ccw_device *cdev)
अणु
	पूर्णांक ret = 0;

	device_lock(&cdev->dev);
	अगर (cmf_enabled(cdev)) अणु
		cmbops->reset(cdev);
		जाओ out_unlock;
	पूर्ण
	get_device(&cdev->dev);
	ret = cmbops->alloc(cdev);
	अगर (ret)
		जाओ out;
	cmbops->reset(cdev);
	ret = sysfs_create_group(&cdev->dev.kobj, cmbops->attr_group);
	अगर (ret) अणु
		cmbops->मुक्त(cdev);
		जाओ out;
	पूर्ण
	ret = cmbops->set(cdev, 2);
	अगर (ret) अणु
		sysfs_हटाओ_group(&cdev->dev.kobj, cmbops->attr_group);
		cmbops->मुक्त(cdev);
	पूर्ण
out:
	अगर (ret)
		put_device(&cdev->dev);
out_unlock:
	device_unlock(&cdev->dev);
	वापस ret;
पूर्ण

/**
 * __disable_cmf() - चयन off the channel measurement क्रम a specअगरic device
 *  @cdev:	The ccw device to be disabled
 *
 *  Returns: %0 क्रम success or a negative error value.
 *
 *  Context:
 *    non-atomic, device_lock() held.
 */
पूर्णांक __disable_cmf(काष्ठा ccw_device *cdev)
अणु
	पूर्णांक ret;

	ret = cmbops->set(cdev, 0);
	अगर (ret)
		वापस ret;

	sysfs_हटाओ_group(&cdev->dev.kobj, cmbops->attr_group);
	cmbops->मुक्त(cdev);
	put_device(&cdev->dev);

	वापस ret;
पूर्ण

/**
 * disable_cmf() - चयन off the channel measurement क्रम a specअगरic device
 *  @cdev:	The ccw device to be disabled
 *
 *  Returns: %0 क्रम success or a negative error value.
 *
 *  Context:
 *    non-atomic
 */
पूर्णांक disable_cmf(काष्ठा ccw_device *cdev)
अणु
	पूर्णांक ret;

	device_lock(&cdev->dev);
	ret = __disable_cmf(cdev);
	device_unlock(&cdev->dev);

	वापस ret;
पूर्ण

/**
 * cmf_पढ़ो() - पढ़ो one value from the current channel measurement block
 * @cdev:	the channel to be पढ़ो
 * @index:	the index of the value to be पढ़ो
 *
 * Returns: The value पढ़ो or %0 अगर the value cannot be पढ़ो.
 *
 *  Context:
 *    any
 */
u64 cmf_पढ़ो(काष्ठा ccw_device *cdev, पूर्णांक index)
अणु
	वापस cmbops->पढ़ो(cdev, index);
पूर्ण

/**
 * cmf_पढ़ोall() - पढ़ो the current channel measurement block
 * @cdev:	the channel to be पढ़ो
 * @data:	a poपूर्णांकer to a data block that will be filled
 *
 * Returns: %0 on success, a negative error value otherwise.
 *
 *  Context:
 *    any
 */
पूर्णांक cmf_पढ़ोall(काष्ठा ccw_device *cdev, काष्ठा cmbdata *data)
अणु
	वापस cmbops->पढ़ोall(cdev, data);
पूर्ण

/* Reenable cmf when a disconnected device becomes available again. */
पूर्णांक cmf_reenable(काष्ठा ccw_device *cdev)
अणु
	cmbops->reset(cdev);
	वापस cmbops->set(cdev, 2);
पूर्ण

/**
 * cmf_reactivate() - reactivate measurement block updates
 *
 * Use this during resume from hibernate.
 */
व्योम cmf_reactivate(व्योम)
अणु
	spin_lock(&cmb_area.lock);
	अगर (!list_empty(&cmb_area.list))
		cmf_activate(cmb_area.mem, CMF_ON);
	spin_unlock(&cmb_area.lock);
पूर्ण

अटल पूर्णांक __init init_cmbe(व्योम)
अणु
	cmbe_cache = kmem_cache_create("cmbe_cache", माप(काष्ठा cmbe),
				       __alignof__(काष्ठा cmbe), 0, शून्य);

	वापस cmbe_cache ? 0 : -ENOMEM;
पूर्ण

अटल पूर्णांक __init init_cmf(व्योम)
अणु
	अक्षर *क्रमmat_string;
	अक्षर *detect_string;
	पूर्णांक ret;

	/*
	 * If the user did not give a parameter, see अगर we are running on a
	 * machine supporting extended measurement blocks, otherwise fall back
	 * to basic mode.
	 */
	अगर (क्रमmat == CMF_AUTODETECT) अणु
		अगर (!css_general_अक्षरacteristics.ext_mb) अणु
			क्रमmat = CMF_BASIC;
		पूर्ण अन्यथा अणु
			क्रमmat = CMF_EXTENDED;
		पूर्ण
		detect_string = "autodetected";
	पूर्ण अन्यथा अणु
		detect_string = "parameter";
	पूर्ण

	चयन (क्रमmat) अणु
	हाल CMF_BASIC:
		क्रमmat_string = "basic";
		cmbops = &cmbops_basic;
		अवरोध;
	हाल CMF_EXTENDED:
		क्रमmat_string = "extended";
		cmbops = &cmbops_extended;

		ret = init_cmbe();
		अगर (ret)
			वापस ret;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	pr_info("Channel measurement facility initialized using format "
		"%s (mode %s)\n", क्रमmat_string, detect_string);
	वापस 0;
पूर्ण
device_initcall(init_cmf);

EXPORT_SYMBOL_GPL(enable_cmf);
EXPORT_SYMBOL_GPL(disable_cmf);
EXPORT_SYMBOL_GPL(cmf_पढ़ो);
EXPORT_SYMBOL_GPL(cmf_पढ़ोall);

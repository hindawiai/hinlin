<शैली गुरु>
/*
 * Remote Processor Framework
 *
 * Copyright(c) 2011 Texas Instruments, Inc.
 * Copyright(c) 2011 Google, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary क्रमm must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the करोcumentation and/or other materials provided with the
 *   distribution.
 * * Neither the name Texas Instruments nor the names of its
 *   contributors may be used to enकरोrse or promote products derived
 *   from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित REMOTEPROC_H
#घोषणा REMOTEPROC_H

#समावेश <linux/types.h>
#समावेश <linux/mutex.h>
#समावेश <linux/virtपन.स>
#समावेश <linux/cdev.h>
#समावेश <linux/completion.h>
#समावेश <linux/idr.h>
#समावेश <linux/of.h>

/**
 * काष्ठा resource_table - firmware resource table header
 * @ver: version number
 * @num: number of resource entries
 * @reserved: reserved (must be zero)
 * @offset: array of offsets poपूर्णांकing at the various resource entries
 *
 * A resource table is essentially a list of प्रणाली resources required
 * by the remote processor. It may also include configuration entries.
 * If needed, the remote processor firmware should contain this table
 * as a dedicated ".resource_table" ELF section.
 *
 * Some resources entries are mere announcements, where the host is inक्रमmed
 * of specअगरic remoteproc configuration. Other entries require the host to
 * करो something (e.g. allocate a प्रणाली resource). Someबार a negotiation
 * is expected, where the firmware requests a resource, and once allocated,
 * the host should provide back its details (e.g. address of an allocated
 * memory region).
 *
 * The header of the resource table, as expressed by this काष्ठाure,
 * contains a version number (should we need to change this क्रमmat in the
 * future), the number of available resource entries, and their offsets
 * in the table.
 *
 * Immediately following this header are the resource entries themselves,
 * each of which begins with a resource entry header (as described below).
 */
काष्ठा resource_table अणु
	u32 ver;
	u32 num;
	u32 reserved[2];
	u32 offset[];
पूर्ण __packed;

/**
 * काष्ठा fw_rsc_hdr - firmware resource entry header
 * @type: resource type
 * @data: resource data
 *
 * Every resource entry begins with a 'struct fw_rsc_hdr' header providing
 * its @type. The content of the entry itself will immediately follow
 * this header, and it should be parsed according to the resource type.
 */
काष्ठा fw_rsc_hdr अणु
	u32 type;
	u8 data[];
पूर्ण __packed;

/**
 * क्रमागत fw_resource_type - types of resource entries
 *
 * @RSC_CARVEOUT:   request क्रम allocation of a physically contiguous
 *		    memory region.
 * @RSC_DEVMEM:     request to iommu_map a memory-based peripheral.
 * @RSC_TRACE:	    announces the availability of a trace buffer पूर्णांकo which
 *		    the remote processor will be writing logs.
 * @RSC_VDEV:       declare support क्रम a virtio device, and serve as its
 *		    virtio header.
 * @RSC_LAST:       just keep this one at the end of standard resources
 * @RSC_VENDOR_START:	start of the venकरोr specअगरic resource types range
 * @RSC_VENDOR_END:	end of the venकरोr specअगरic resource types range
 *
 * For more details regarding a specअगरic resource type, please see its
 * dedicated काष्ठाure below.
 *
 * Please note that these values are used as indices to the rproc_handle_rsc
 * lookup table, so please keep them sane. Moreover, @RSC_LAST is used to
 * check the validity of an index beक्रमe the lookup table is accessed, so
 * please update it as needed.
 */
क्रमागत fw_resource_type अणु
	RSC_CARVEOUT		= 0,
	RSC_DEVMEM		= 1,
	RSC_TRACE		= 2,
	RSC_VDEV		= 3,
	RSC_LAST		= 4,
	RSC_VENDOR_START	= 128,
	RSC_VENDOR_END		= 512,
पूर्ण;

#घोषणा FW_RSC_ADDR_ANY (-1)

/**
 * काष्ठा fw_rsc_carveout - physically contiguous memory request
 * @da: device address
 * @pa: physical address
 * @len: length (in bytes)
 * @flags: iommu protection flags
 * @reserved: reserved (must be zero)
 * @name: human-पढ़ोable name of the requested memory region
 *
 * This resource entry requests the host to allocate a physically contiguous
 * memory region.
 *
 * These request entries should precede other firmware resource entries,
 * as other entries might request placing other data objects inside
 * these memory regions (e.g. data/code segments, trace resource entries, ...).
 *
 * Allocating memory this way helps utilizing the reserved physical memory
 * (e.g. CMA) more efficiently, and also minimizes the number of TLB entries
 * needed to map it (in हाल @rproc is using an IOMMU). Reducing the TLB
 * pressure is important; it may have a substantial impact on perक्रमmance.
 *
 * If the firmware is compiled with अटल addresses, then @da should specअगरy
 * the expected device address of this memory region. If @da is set to
 * FW_RSC_ADDR_ANY, then the host will dynamically allocate it, and then
 * overग_लिखो @da with the dynamically allocated address.
 *
 * We will always use @da to negotiate the device addresses, even अगर it
 * isn't using an iommu. In that हाल, though, it will obviously contain
 * physical addresses.
 *
 * Some remote processors needs to know the allocated physical address
 * even अगर they करो use an iommu. This is needed, e.g., अगर they control
 * hardware accelerators which access the physical memory directly (this
 * is the हाल with OMAP4 क्रम instance). In that हाल, the host will
 * overग_लिखो @pa with the dynamically allocated physical address.
 * Generally we करोn't want to expose physical addresses if we don't have to
 * (remote processors are generally _not_ trusted), so we might want to
 * change this to happen _only_ when explicitly required by the hardware.
 *
 * @flags is used to provide IOMMU protection flags, and @name should
 * (optionally) contain a human पढ़ोable name of this carveout region
 * (मुख्यly क्रम debugging purposes).
 */
काष्ठा fw_rsc_carveout अणु
	u32 da;
	u32 pa;
	u32 len;
	u32 flags;
	u32 reserved;
	u8 name[32];
पूर्ण __packed;

/**
 * काष्ठा fw_rsc_devmem - iommu mapping request
 * @da: device address
 * @pa: physical address
 * @len: length (in bytes)
 * @flags: iommu protection flags
 * @reserved: reserved (must be zero)
 * @name: human-पढ़ोable name of the requested region to be mapped
 *
 * This resource entry requests the host to iommu map a physically contiguous
 * memory region. This is needed in हाल the remote processor requires
 * access to certain memory-based peripherals; _never_ use it to access
 * regular memory.
 *
 * This is obviously only needed अगर the remote processor is accessing memory
 * via an iommu.
 *
 * @da should specअगरy the required device address, @pa should specअगरy
 * the physical address we want to map, @len should specअगरy the size of
 * the mapping and @flags is the IOMMU protection flags. As always, @name may
 * (optionally) contain a human पढ़ोable name of this mapping (मुख्यly क्रम
 * debugging purposes).
 *
 * Note: at this poपूर्णांक we just "trust" those devmem entries to contain valid
 * physical addresses, but this isn't safe and will be changed: eventually we
 * want remoteproc implementations to provide us ranges of physical addresses
 * the firmware is allowed to request, and not allow firmwares to request
 * access to physical addresses that are outside those ranges.
 */
काष्ठा fw_rsc_devmem अणु
	u32 da;
	u32 pa;
	u32 len;
	u32 flags;
	u32 reserved;
	u8 name[32];
पूर्ण __packed;

/**
 * काष्ठा fw_rsc_trace - trace buffer declaration
 * @da: device address
 * @len: length (in bytes)
 * @reserved: reserved (must be zero)
 * @name: human-पढ़ोable name of the trace buffer
 *
 * This resource entry provides the host inक्रमmation about a trace buffer
 * पूर्णांकo which the remote processor will ग_लिखो log messages.
 *
 * @da specअगरies the device address of the buffer, @len specअगरies
 * its size, and @name may contain a human पढ़ोable name of the trace buffer.
 *
 * After booting the remote processor, the trace buffers are exposed to the
 * user via debugfs entries (called trace0, trace1, etc..).
 */
काष्ठा fw_rsc_trace अणु
	u32 da;
	u32 len;
	u32 reserved;
	u8 name[32];
पूर्ण __packed;

/**
 * काष्ठा fw_rsc_vdev_vring - vring descriptor entry
 * @da: device address
 * @align: the alignment between the consumer and producer parts of the vring
 * @num: num of buffers supported by this vring (must be घातer of two)
 * @notअगरyid is a unique rproc-wide notअगरy index क्रम this vring. This notअगरy
 * index is used when kicking a remote processor, to let it know that this
 * vring is triggered.
 * @pa: physical address
 *
 * This descriptor is not a resource entry by itself; it is part of the
 * vdev resource type (see below).
 *
 * Note that @da should either contain the device address where
 * the remote processor is expecting the vring, or indicate that
 * dynamically allocation of the vring's device address is supported.
 */
काष्ठा fw_rsc_vdev_vring अणु
	u32 da;
	u32 align;
	u32 num;
	u32 notअगरyid;
	u32 pa;
पूर्ण __packed;

/**
 * काष्ठा fw_rsc_vdev - virtio device header
 * @id: virtio device id (as in virtio_ids.h)
 * @notअगरyid is a unique rproc-wide notअगरy index क्रम this vdev. This notअगरy
 * index is used when kicking a remote processor, to let it know that the
 * status/features of this vdev have changes.
 * @dfeatures specअगरies the virtio device features supported by the firmware
 * @gfeatures is a place holder used by the host to ग_लिखो back the
 * negotiated features that are supported by both sides.
 * @config_len is the size of the virtio config space of this vdev. The config
 * space lies in the resource table immediate after this vdev header.
 * @status is a place holder where the host will indicate its virtio progress.
 * @num_of_vrings indicates how many vrings are described in this vdev header
 * @reserved: reserved (must be zero)
 * @vring is an array of @num_of_vrings entries of 'struct fw_rsc_vdev_vring'.
 *
 * This resource is a virtio device header: it provides inक्रमmation about
 * the vdev, and is then used by the host and its peer remote processors
 * to negotiate and share certain virtio properties.
 *
 * By providing this resource entry, the firmware essentially asks remoteproc
 * to अटलally allocate a vdev upon registration of the rproc (dynamic vdev
 * allocation is not yet supported).
 *
 * Note: unlike भवization प्रणालीs, the term 'host' here means
 * the Linux side which is running remoteproc to control the remote
 * processors. We use the name 'gfeatures' to comply with virtio's terms,
 * though there isn't really any virtualized guest OS here: it's the host
 * which is responsible क्रम negotiating the final features.
 * Yeah, it's a bit confusing.
 *
 * Note: immediately following this काष्ठाure is the virtio config space क्रम
 * this vdev (which is specअगरic to the vdev; क्रम more info, पढ़ो the virtio
 * spec). the size of the config space is specअगरied by @config_len.
 */
काष्ठा fw_rsc_vdev अणु
	u32 id;
	u32 notअगरyid;
	u32 dfeatures;
	u32 gfeatures;
	u32 config_len;
	u8 status;
	u8 num_of_vrings;
	u8 reserved[2];
	काष्ठा fw_rsc_vdev_vring vring[];
पूर्ण __packed;

काष्ठा rproc;

/**
 * काष्ठा rproc_mem_entry - memory entry descriptor
 * @va:	भव address
 * @is_iomem: io memory
 * @dma: dma address
 * @len: length, in bytes
 * @da: device address
 * @release: release associated memory
 * @priv: associated data
 * @name: associated memory region name (optional)
 * @node: list node
 * @rsc_offset: offset in resource table
 * @flags: iommu protection flags
 * @of_resm_idx: reserved memory phandle index
 * @alloc: specअगरic memory allocator function
 */
काष्ठा rproc_mem_entry अणु
	व्योम *va;
	bool is_iomem;
	dma_addr_t dma;
	माप_प्रकार len;
	u32 da;
	व्योम *priv;
	अक्षर name[32];
	काष्ठा list_head node;
	u32 rsc_offset;
	u32 flags;
	u32 of_resm_idx;
	पूर्णांक (*alloc)(काष्ठा rproc *rproc, काष्ठा rproc_mem_entry *mem);
	पूर्णांक (*release)(काष्ठा rproc *rproc, काष्ठा rproc_mem_entry *mem);
पूर्ण;

काष्ठा firmware;

/**
 * क्रमागत rsc_handling_status - वापस status of rproc_ops handle_rsc hook
 * @RSC_HANDLED:	resource was handled
 * @RSC_IGNORED:	resource was ignored
 */
क्रमागत rsc_handling_status अणु
	RSC_HANDLED	= 0,
	RSC_IGNORED	= 1,
पूर्ण;

/**
 * काष्ठा rproc_ops - platक्रमm-specअगरic device handlers
 * @prepare:	prepare device क्रम code loading
 * @unprepare:	unprepare device after stop
 * @start:	घातer on the device and boot it
 * @stop:	घातer off the device
 * @attach:	attach to a device that his alपढ़ोy घातered up
 * @detach:	detach from a device, leaving it घातered up
 * @kick:	kick a virtqueue (virtqueue id given as a parameter)
 * @da_to_va:	optional platक्रमm hook to perक्रमm address translations
 * @parse_fw:	parse firmware to extract inक्रमmation (e.g. resource table)
 * @handle_rsc:	optional platक्रमm hook to handle venकरोr resources. Should वापस
 * RSC_HANDLED अगर resource was handled, RSC_IGNORED अगर not handled and a
 * negative value on error
 * @load_rsc_table:	load resource table from firmware image
 * @find_loaded_rsc_table: find the loaded resource table from firmware image
 * @get_loaded_rsc_table: get resource table installed in memory
 *			  by बाह्यal entity
 * @load:		load firmware to memory, where the remote processor
 *			expects to find it
 * @sanity_check:	sanity check the fw image
 * @get_boot_addr:	get boot address to entry poपूर्णांक specअगरied in firmware
 * @panic:	optional callback to react to प्रणाली panic, core will delay
 *		panic at least the वापसed number of milliseconds
 * @coredump:	  collect firmware dump after the subप्रणाली is shutकरोwn
 */
काष्ठा rproc_ops अणु
	पूर्णांक (*prepare)(काष्ठा rproc *rproc);
	पूर्णांक (*unprepare)(काष्ठा rproc *rproc);
	पूर्णांक (*start)(काष्ठा rproc *rproc);
	पूर्णांक (*stop)(काष्ठा rproc *rproc);
	पूर्णांक (*attach)(काष्ठा rproc *rproc);
	पूर्णांक (*detach)(काष्ठा rproc *rproc);
	व्योम (*kick)(काष्ठा rproc *rproc, पूर्णांक vqid);
	व्योम * (*da_to_va)(काष्ठा rproc *rproc, u64 da, माप_प्रकार len, bool *is_iomem);
	पूर्णांक (*parse_fw)(काष्ठा rproc *rproc, स्थिर काष्ठा firmware *fw);
	पूर्णांक (*handle_rsc)(काष्ठा rproc *rproc, u32 rsc_type, व्योम *rsc,
			  पूर्णांक offset, पूर्णांक avail);
	काष्ठा resource_table *(*find_loaded_rsc_table)(
				काष्ठा rproc *rproc, स्थिर काष्ठा firmware *fw);
	काष्ठा resource_table *(*get_loaded_rsc_table)(
				काष्ठा rproc *rproc, माप_प्रकार *size);
	पूर्णांक (*load)(काष्ठा rproc *rproc, स्थिर काष्ठा firmware *fw);
	पूर्णांक (*sanity_check)(काष्ठा rproc *rproc, स्थिर काष्ठा firmware *fw);
	u64 (*get_boot_addr)(काष्ठा rproc *rproc, स्थिर काष्ठा firmware *fw);
	अचिन्हित दीर्घ (*panic)(काष्ठा rproc *rproc);
	व्योम (*coredump)(काष्ठा rproc *rproc);
पूर्ण;

/**
 * क्रमागत rproc_state - remote processor states
 * @RPROC_OFFLINE:	device is घातered off
 * @RPROC_SUSPENDED:	device is suspended; needs to be woken up to receive
 *			a message.
 * @RPROC_RUNNING:	device is up and running
 * @RPROC_CRASHED:	device has crashed; need to start recovery
 * @RPROC_DELETED:	device is deleted
 * @RPROC_ATTACHED:	device has been booted by another entity and the core
 *			has attached to it
 * @RPROC_DETACHED:	device has been booted by another entity and रुकोing
 *			क्रम the core to attach to it
 * @RPROC_LAST:		just keep this one at the end
 *
 * Please note that the values of these states are used as indices
 * to rproc_state_string, a state-to-name lookup table,
 * so please keep the two synchronized. @RPROC_LAST is used to check
 * the validity of an index beक्रमe the lookup table is accessed, so
 * please update it as needed too.
 */
क्रमागत rproc_state अणु
	RPROC_OFFLINE	= 0,
	RPROC_SUSPENDED	= 1,
	RPROC_RUNNING	= 2,
	RPROC_CRASHED	= 3,
	RPROC_DELETED	= 4,
	RPROC_ATTACHED	= 5,
	RPROC_DETACHED	= 6,
	RPROC_LAST	= 7,
पूर्ण;

/**
 * क्रमागत rproc_crash_type - remote processor crash types
 * @RPROC_MMUFAULT:	iommu fault
 * @RPROC_WATCHDOG:	watchकरोg bite
 * @RPROC_FATAL_ERROR	fatal error
 *
 * Each element of the क्रमागत is used as an array index. So that, the value of
 * the elements should be always something sane.
 *
 * Feel मुक्त to add more types when needed.
 */
क्रमागत rproc_crash_type अणु
	RPROC_MMUFAULT,
	RPROC_WATCHDOG,
	RPROC_FATAL_ERROR,
पूर्ण;

/**
 * क्रमागत rproc_dump_mechanism - Coredump options क्रम core
 * @RPROC_COREDUMP_DISABLED:	Don't perक्रमm any dump
 * @RPROC_COREDUMP_ENABLED:	Copy dump to separate buffer and carry on with
				recovery
 * @RPROC_COREDUMP_INLINE:	Read segments directly from device memory. Stall
				recovery until all segments are पढ़ो
 */
क्रमागत rproc_dump_mechanism अणु
	RPROC_COREDUMP_DISABLED,
	RPROC_COREDUMP_ENABLED,
	RPROC_COREDUMP_INLINE,
पूर्ण;

/**
 * काष्ठा rproc_dump_segment - segment info from ELF header
 * @node:	list node related to the rproc segment list
 * @da:		device address of the segment
 * @size:	size of the segment
 * @priv:	निजी data associated with the dump_segment
 * @dump:	custom dump function to fill device memory segment associated
 *		with coredump
 */
काष्ठा rproc_dump_segment अणु
	काष्ठा list_head node;

	dma_addr_t da;
	माप_प्रकार size;

	व्योम *priv;
	व्योम (*dump)(काष्ठा rproc *rproc, काष्ठा rproc_dump_segment *segment,
		     व्योम *dest, माप_प्रकार offset, माप_प्रकार size);
	loff_t offset;
पूर्ण;

/**
 * काष्ठा rproc - represents a physical remote processor device
 * @node: list node of this rproc object
 * @करोमुख्य: iommu करोमुख्य
 * @name: human पढ़ोable name of the rproc
 * @firmware: name of firmware file to be loaded
 * @priv: निजी data which beदीर्घs to the platक्रमm-specअगरic rproc module
 * @ops: platक्रमm-specअगरic start/stop rproc handlers
 * @dev: भव device क्रम refcounting and common remoteproc behavior
 * @घातer: refcount of users who need this rproc घातered up
 * @state: state of the device
 * @dump_conf: Currently selected coredump configuration
 * @lock: lock which protects concurrent manipulations of the rproc
 * @dbg_dir: debugfs directory of this rproc device
 * @traces: list of trace buffers
 * @num_traces: number of trace buffers
 * @carveouts: list of physically contiguous memory allocations
 * @mappings: list of iommu mappings we initiated, needed on shutकरोwn
 * @bootaddr: address of first inकाष्ठाion to boot rproc with (optional)
 * @rvdevs: list of remote virtio devices
 * @subdevs: list of subdevices, to following the running state
 * @notअगरyids: idr क्रम dynamically assigning rproc-wide unique notअगरy ids
 * @index: index of this rproc device
 * @crash_handler: workqueue क्रम handling a crash
 * @crash_cnt: crash counter
 * @recovery_disabled: flag that state अगर recovery was disabled
 * @max_notअगरyid: largest allocated notअगरy id.
 * @table_ptr: poपूर्णांकer to the resource table in effect
 * @clean_table: copy of the resource table without modअगरications.  Used
 *		 when a remote processor is attached or detached from the core
 * @cached_table: copy of the resource table
 * @table_sz: size of @cached_table
 * @has_iommu: flag to indicate अगर remote processor is behind an MMU
 * @स्वतः_boot: flag to indicate अगर remote processor should be स्वतः-started
 * @dump_segments: list of segments in the firmware
 * @nb_vdev: number of vdev currently handled by rproc
 * @अक्षर_dev: अक्षरacter device of the rproc
 * @cdev_put_on_release: flag to indicate अगर remoteproc should be shutकरोwn on @अक्षर_dev release
 */
काष्ठा rproc अणु
	काष्ठा list_head node;
	काष्ठा iommu_करोमुख्य *करोमुख्य;
	स्थिर अक्षर *name;
	स्थिर अक्षर *firmware;
	व्योम *priv;
	काष्ठा rproc_ops *ops;
	काष्ठा device dev;
	atomic_t घातer;
	अचिन्हित पूर्णांक state;
	क्रमागत rproc_dump_mechanism dump_conf;
	काष्ठा mutex lock;
	काष्ठा dentry *dbg_dir;
	काष्ठा list_head traces;
	पूर्णांक num_traces;
	काष्ठा list_head carveouts;
	काष्ठा list_head mappings;
	u64 bootaddr;
	काष्ठा list_head rvdevs;
	काष्ठा list_head subdevs;
	काष्ठा idr notअगरyids;
	पूर्णांक index;
	काष्ठा work_काष्ठा crash_handler;
	अचिन्हित पूर्णांक crash_cnt;
	bool recovery_disabled;
	पूर्णांक max_notअगरyid;
	काष्ठा resource_table *table_ptr;
	काष्ठा resource_table *clean_table;
	काष्ठा resource_table *cached_table;
	माप_प्रकार table_sz;
	bool has_iommu;
	bool स्वतः_boot;
	काष्ठा list_head dump_segments;
	पूर्णांक nb_vdev;
	u8 elf_class;
	u16 elf_machine;
	काष्ठा cdev cdev;
	bool cdev_put_on_release;
पूर्ण;

/**
 * काष्ठा rproc_subdev - subdevice tied to a remoteproc
 * @node: list node related to the rproc subdevs list
 * @prepare: prepare function, called beक्रमe the rproc is started
 * @start: start function, called after the rproc has been started
 * @stop: stop function, called beक्रमe the rproc is stopped; the @crashed
 *	    parameter indicates अगर this originates from a recovery
 * @unprepare: unprepare function, called after the rproc has been stopped
 */
काष्ठा rproc_subdev अणु
	काष्ठा list_head node;

	पूर्णांक (*prepare)(काष्ठा rproc_subdev *subdev);
	पूर्णांक (*start)(काष्ठा rproc_subdev *subdev);
	व्योम (*stop)(काष्ठा rproc_subdev *subdev, bool crashed);
	व्योम (*unprepare)(काष्ठा rproc_subdev *subdev);
पूर्ण;

/* we currently support only two vrings per rvdev */

#घोषणा RVDEV_NUM_VRINGS 2

/**
 * काष्ठा rproc_vring - remoteproc vring state
 * @va:	भव address
 * @len: length, in bytes
 * @da: device address
 * @align: vring alignment
 * @notअगरyid: rproc-specअगरic unique vring index
 * @rvdev: remote vdev
 * @vq: the virtqueue of this vring
 */
काष्ठा rproc_vring अणु
	व्योम *va;
	पूर्णांक len;
	u32 da;
	u32 align;
	पूर्णांक notअगरyid;
	काष्ठा rproc_vdev *rvdev;
	काष्ठा virtqueue *vq;
पूर्ण;

/**
 * काष्ठा rproc_vdev - remoteproc state क्रम a supported virtio device
 * @refcount: reference counter क्रम the vdev and vring allocations
 * @subdev: handle क्रम रेजिस्टरing the vdev as a rproc subdevice
 * @id: virtio device id (as in virtio_ids.h)
 * @node: list node
 * @rproc: the rproc handle
 * @vdev: the virio device
 * @vring: the vrings क्रम this vdev
 * @rsc_offset: offset of the vdev's resource entry
 * @index: vdev position versus other vdev declared in resource table
 */
काष्ठा rproc_vdev अणु
	काष्ठा kref refcount;

	काष्ठा rproc_subdev subdev;
	काष्ठा device dev;

	अचिन्हित पूर्णांक id;
	काष्ठा list_head node;
	काष्ठा rproc *rproc;
	काष्ठा rproc_vring vring[RVDEV_NUM_VRINGS];
	u32 rsc_offset;
	u32 index;
पूर्ण;

काष्ठा rproc *rproc_get_by_phandle(phandle phandle);
काष्ठा rproc *rproc_get_by_child(काष्ठा device *dev);

काष्ठा rproc *rproc_alloc(काष्ठा device *dev, स्थिर अक्षर *name,
			  स्थिर काष्ठा rproc_ops *ops,
			  स्थिर अक्षर *firmware, पूर्णांक len);
व्योम rproc_put(काष्ठा rproc *rproc);
पूर्णांक rproc_add(काष्ठा rproc *rproc);
पूर्णांक rproc_del(काष्ठा rproc *rproc);
व्योम rproc_मुक्त(काष्ठा rproc *rproc);
व्योम rproc_resource_cleanup(काष्ठा rproc *rproc);

काष्ठा rproc *devm_rproc_alloc(काष्ठा device *dev, स्थिर अक्षर *name,
			       स्थिर काष्ठा rproc_ops *ops,
			       स्थिर अक्षर *firmware, पूर्णांक len);
पूर्णांक devm_rproc_add(काष्ठा device *dev, काष्ठा rproc *rproc);

व्योम rproc_add_carveout(काष्ठा rproc *rproc, काष्ठा rproc_mem_entry *mem);

काष्ठा rproc_mem_entry *
rproc_mem_entry_init(काष्ठा device *dev,
		     व्योम *va, dma_addr_t dma, माप_प्रकार len, u32 da,
		     पूर्णांक (*alloc)(काष्ठा rproc *, काष्ठा rproc_mem_entry *),
		     पूर्णांक (*release)(काष्ठा rproc *, काष्ठा rproc_mem_entry *),
		     स्थिर अक्षर *name, ...);

काष्ठा rproc_mem_entry *
rproc_of_resm_mem_entry_init(काष्ठा device *dev, u32 of_resm_idx, माप_प्रकार len,
			     u32 da, स्थिर अक्षर *name, ...);

पूर्णांक rproc_boot(काष्ठा rproc *rproc);
व्योम rproc_shutकरोwn(काष्ठा rproc *rproc);
पूर्णांक rproc_detach(काष्ठा rproc *rproc);
पूर्णांक rproc_set_firmware(काष्ठा rproc *rproc, स्थिर अक्षर *fw_name);
व्योम rproc_report_crash(काष्ठा rproc *rproc, क्रमागत rproc_crash_type type);
व्योम rproc_coredump_using_sections(काष्ठा rproc *rproc);
पूर्णांक rproc_coredump_add_segment(काष्ठा rproc *rproc, dma_addr_t da, माप_प्रकार size);
पूर्णांक rproc_coredump_add_custom_segment(काष्ठा rproc *rproc,
				      dma_addr_t da, माप_प्रकार size,
				      व्योम (*dumpfn)(काष्ठा rproc *rproc,
						     काष्ठा rproc_dump_segment *segment,
						     व्योम *dest, माप_प्रकार offset,
						     माप_प्रकार size),
				      व्योम *priv);
पूर्णांक rproc_coredump_set_elf_info(काष्ठा rproc *rproc, u8 class, u16 machine);

अटल अंतरभूत काष्ठा rproc_vdev *vdev_to_rvdev(काष्ठा virtio_device *vdev)
अणु
	वापस container_of(vdev->dev.parent, काष्ठा rproc_vdev, dev);
पूर्ण

अटल अंतरभूत काष्ठा rproc *vdev_to_rproc(काष्ठा virtio_device *vdev)
अणु
	काष्ठा rproc_vdev *rvdev = vdev_to_rvdev(vdev);

	वापस rvdev->rproc;
पूर्ण

व्योम rproc_add_subdev(काष्ठा rproc *rproc, काष्ठा rproc_subdev *subdev);

व्योम rproc_हटाओ_subdev(काष्ठा rproc *rproc, काष्ठा rproc_subdev *subdev);

#पूर्ण_अगर /* REMOTEPROC_H */

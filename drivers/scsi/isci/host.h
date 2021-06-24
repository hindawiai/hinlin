<शैली गुरु>
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * Copyright(c) 2008 - 2011 Intel Corporation. All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St - Fअगरth Floor, Boston, MA 02110-1301 USA.
 * The full GNU General Public License is included in this distribution
 * in the file called LICENSE.GPL.
 *
 * BSD LICENSE
 *
 * Copyright(c) 2008 - 2011 Intel Corporation. All rights reserved.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary क्रमm must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the करोcumentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Intel Corporation nor the names of its
 *     contributors may be used to enकरोrse or promote products derived
 *     from this software without specअगरic prior written permission.
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
#अगर_अघोषित _SCI_HOST_H_
#घोषणा _SCI_HOST_H_

#समावेश <scsi/sas_ata.h>
#समावेश "remote_device.h"
#समावेश "phy.h"
#समावेश "isci.h"
#समावेश "remote_node_table.h"
#समावेश "registers.h"
#समावेश "unsolicited_frame_control.h"
#समावेश "probe_roms.h"

काष्ठा isci_request;
काष्ठा scu_task_context;


/**
 * काष्ठा sci_घातer_control -
 *
 * This काष्ठाure defines the fields क्रम managing घातer control क्रम direct
 * attached disk devices.
 */
काष्ठा sci_घातer_control अणु
	/**
	 * This field is set when the घातer control समयr is running and cleared when
	 * it is not.
	 */
	bool समयr_started;

	/**
	 * Timer to control when the directed attached disks can consume घातer.
	 */
	काष्ठा sci_समयr समयr;

	/**
	 * This field is used to keep track of how many phys are put पूर्णांकo the
	 * requesters field.
	 */
	u8 phys_रुकोing;

	/**
	 * This field is used to keep track of how many phys have been granted to consume घातer
	 */
	u8 phys_granted_घातer;

	/**
	 * This field is an array of phys that we are रुकोing on. The phys are direct
	 * mapped पूर्णांकo requesters via काष्ठा sci_phy.phy_index
	 */
	काष्ठा isci_phy *requesters[SCI_MAX_PHYS];

पूर्ण;

काष्ठा sci_port_configuration_agent;
प्रकार व्योम (*port_config_fn)(काष्ठा isci_host *,
			       काष्ठा sci_port_configuration_agent *,
			       काष्ठा isci_port *, काष्ठा isci_phy *);
bool is_port_config_apc(काष्ठा isci_host *ihost);
bool is_controller_start_complete(काष्ठा isci_host *ihost);

काष्ठा sci_port_configuration_agent अणु
	u16 phy_configured_mask;
	u16 phy_पढ़ोy_mask;
	काष्ठा अणु
		u8 min_index;
		u8 max_index;
	पूर्ण phy_valid_port_range[SCI_MAX_PHYS];
	bool समयr_pending;
	port_config_fn link_up_handler;
	port_config_fn link_करोwn_handler;
	काष्ठा sci_समयr	समयr;
पूर्ण;

/**
 * isci_host - primary host/controller object
 * @समयr: समयout start/stop operations
 * @device_table: rni (hw remote node index) to remote device lookup table
 * @available_remote_nodes: rni allocator
 * @घातer_control: manage device spin up
 * @io_request_sequence: generation number क्रम tci's (task contexts)
 * @task_context_table: hw task context table
 * @remote_node_context_table: hw remote node context table
 * @completion_queue: hw-producer driver-consumer communication ring
 * @completion_queue_get: tracks the driver 'head' of the ring to notअगरy hw
 * @logical_port_entries: min(अणुdriver|siliconपूर्ण-supported-port-count)
 * @remote_node_entries: min(अणुdriver|siliconपूर्ण-supported-node-count)
 * @task_context_entries: min(अणुdriver|siliconपूर्ण-supported-task-count)
 * @phy_समयr: phy startup समयr
 * @invalid_phy_mask: अगर an invalid_link_up notअगरication is reported a bit क्रम
 * 		      the phy index is set so further notअगरications are not
 * 		      made.  Once the phy reports link up and is made part of a
 * 		      port then this bit is cleared.

 */
काष्ठा isci_host अणु
	काष्ठा sci_base_state_machine sm;
	/* XXX can we समय this बाह्यally */
	काष्ठा sci_समयr समयr;
	/* XXX drop reference module params directly */
	काष्ठा sci_user_parameters user_parameters;
	/* XXX no need to be a जोड़ */
	काष्ठा sci_oem_params oem_parameters;
	काष्ठा sci_port_configuration_agent port_agent;
	काष्ठा isci_remote_device *device_table[SCI_MAX_REMOTE_DEVICES];
	काष्ठा sci_remote_node_table available_remote_nodes;
	काष्ठा sci_घातer_control घातer_control;
	u8 io_request_sequence[SCI_MAX_IO_REQUESTS];
	काष्ठा scu_task_context *task_context_table;
	dma_addr_t tc_dma;
	जोड़ scu_remote_node_context *remote_node_context_table;
	dma_addr_t rnc_dma;
	u32 *completion_queue;
	dma_addr_t cq_dma;
	u32 completion_queue_get;
	u32 logical_port_entries;
	u32 remote_node_entries;
	u32 task_context_entries;
	व्योम *ufi_buf;
	dma_addr_t ufi_dma;
	काष्ठा sci_unsolicited_frame_control uf_control;

	/* phy startup */
	काष्ठा sci_समयr phy_समयr;
	/* XXX समाप्त */
	bool phy_startup_समयr_pending;
	u32 next_phy_to_start;
	/* XXX convert to अचिन्हित दीर्घ and use bitops */
	u8 invalid_phy_mask;

	/* TODO attempt dynamic पूर्णांकerrupt coalescing scheme */
	u16 पूर्णांकerrupt_coalesce_number;
	u32 पूर्णांकerrupt_coalesce_समयout;
	काष्ठा smu_रेजिस्टरs __iomem *smu_रेजिस्टरs;
	काष्ठा scu_रेजिस्टरs __iomem *scu_रेजिस्टरs;

	u16 tci_head;
	u16 tci_tail;
	u16 tci_pool[SCI_MAX_IO_REQUESTS];

	पूर्णांक id; /* unique within a given pci device */
	काष्ठा isci_phy phys[SCI_MAX_PHYS];
	काष्ठा isci_port ports[SCI_MAX_PORTS + 1]; /* includes dummy port */
	काष्ठा asd_sas_port sas_ports[SCI_MAX_PORTS];
	काष्ठा sas_ha_काष्ठा sas_ha;

	काष्ठा pci_dev *pdev;
	#घोषणा IHOST_START_PENDING 0
	#घोषणा IHOST_STOP_PENDING 1
	#घोषणा IHOST_IRQ_ENABLED 2
	अचिन्हित दीर्घ flags;
	रुको_queue_head_t eventq;
	काष्ठा tasklet_काष्ठा completion_tasklet;
	spinlock_t scic_lock;
	काष्ठा isci_request *reqs[SCI_MAX_IO_REQUESTS];
	काष्ठा isci_remote_device devices[SCI_MAX_REMOTE_DEVICES];
पूर्ण;

/**
 * क्रमागत sci_controller_states - This क्रमागतeration depicts all the states
 *    क्रम the common controller state machine.
 */
क्रमागत sci_controller_states अणु
	/**
	 * Simply the initial state क्रम the base controller state machine.
	 */
	SCIC_INITIAL = 0,

	/**
	 * This state indicates that the controller is reset.  The memory क्रम
	 * the controller is in it's initial state, but the controller requires
	 * initialization.
	 * This state is entered from the INITIAL state.
	 * This state is entered from the RESETTING state.
	 */
	SCIC_RESET,

	/**
	 * This state is typically an action state that indicates the controller
	 * is in the process of initialization.  In this state no new IO operations
	 * are permitted.
	 * This state is entered from the RESET state.
	 */
	SCIC_INITIALIZING,

	/**
	 * This state indicates that the controller has been successfully
	 * initialized.  In this state no new IO operations are permitted.
	 * This state is entered from the INITIALIZING state.
	 */
	SCIC_INITIALIZED,

	/**
	 * This state indicates the the controller is in the process of becoming
	 * पढ़ोy (i.e. starting).  In this state no new IO operations are permitted.
	 * This state is entered from the INITIALIZED state.
	 */
	SCIC_STARTING,

	/**
	 * This state indicates the controller is now पढ़ोy.  Thus, the user
	 * is able to perक्रमm IO operations on the controller.
	 * This state is entered from the STARTING state.
	 */
	SCIC_READY,

	/**
	 * This state is typically an action state that indicates the controller
	 * is in the process of resetting.  Thus, the user is unable to perक्रमm
	 * IO operations on the controller.  A reset is considered deकाष्ठाive in
	 * most हालs.
	 * This state is entered from the READY state.
	 * This state is entered from the FAILED state.
	 * This state is entered from the STOPPED state.
	 */
	SCIC_RESETTING,

	/**
	 * This state indicates that the controller is in the process of stopping.
	 * In this state no new IO operations are permitted, but existing IO
	 * operations are allowed to complete.
	 * This state is entered from the READY state.
	 */
	SCIC_STOPPING,

	/**
	 * This state indicates that the controller could not successfully be
	 * initialized.  In this state no new IO operations are permitted.
	 * This state is entered from the INITIALIZING state.
	 * This state is entered from the STARTING state.
	 * This state is entered from the STOPPING state.
	 * This state is entered from the RESETTING state.
	 */
	SCIC_FAILED,
पूर्ण;

/**
 * काष्ठा isci_pci_info - This class represents the pci function containing the
 *    controllers. Depending on PCI SKU, there could be up to 2 controllers in
 *    the PCI function.
 */
#घोषणा SCI_MAX_MSIX_INT (SCI_NUM_MSI_X_INT*SCI_MAX_CONTROLLERS)

काष्ठा isci_pci_info अणु
	काष्ठा isci_host *hosts[SCI_MAX_CONTROLLERS];
	काष्ठा isci_orom *orom;
पूर्ण;

अटल अंतरभूत काष्ठा isci_pci_info *to_pci_info(काष्ठा pci_dev *pdev)
अणु
	वापस pci_get_drvdata(pdev);
पूर्ण

अटल अंतरभूत काष्ठा Scsi_Host *to_shost(काष्ठा isci_host *ihost)
अणु
	वापस ihost->sas_ha.core.shost;
पूर्ण

#घोषणा क्रम_each_isci_host(id, ihost, pdev) \
	क्रम (id = 0; id < SCI_MAX_CONTROLLERS && \
	     (ihost = to_pci_info(pdev)->hosts[id]); id++)

अटल अंतरभूत व्योम रुको_क्रम_start(काष्ठा isci_host *ihost)
अणु
	रुको_event(ihost->eventq, !test_bit(IHOST_START_PENDING, &ihost->flags));
पूर्ण

अटल अंतरभूत व्योम रुको_क्रम_stop(काष्ठा isci_host *ihost)
अणु
	रुको_event(ihost->eventq, !test_bit(IHOST_STOP_PENDING, &ihost->flags));
पूर्ण

अटल अंतरभूत व्योम रुको_क्रम_device_start(काष्ठा isci_host *ihost, काष्ठा isci_remote_device *idev)
अणु
	रुको_event(ihost->eventq, !test_bit(IDEV_START_PENDING, &idev->flags));
पूर्ण

अटल अंतरभूत व्योम रुको_क्रम_device_stop(काष्ठा isci_host *ihost, काष्ठा isci_remote_device *idev)
अणु
	रुको_event(ihost->eventq, !test_bit(IDEV_STOP_PENDING, &idev->flags));
पूर्ण

अटल अंतरभूत काष्ठा isci_host *dev_to_ihost(काष्ठा करोमुख्य_device *dev)
अणु
	वापस dev->port->ha->lldd_ha;
पूर्ण

अटल अंतरभूत काष्ठा isci_host *idev_to_ihost(काष्ठा isci_remote_device *idev)
अणु
	वापस dev_to_ihost(idev->करोमुख्य_dev);
पूर्ण

/* we always use protocol engine group zero */
#घोषणा ISCI_PEG 0

/* see sci_controller_io_tag_allocate|मुक्त क्रम how seq and tci are built */
#घोषणा ISCI_TAG(seq, tci) (((u16) (seq)) << 12 | tci)

/* these are वापसed by the hardware, so sanitize them */
#घोषणा ISCI_TAG_SEQ(tag) (((tag) >> 12) & (SCI_MAX_SEQ-1))
#घोषणा ISCI_TAG_TCI(tag) ((tag) & (SCI_MAX_IO_REQUESTS-1))

/* पूर्णांकerrupt coalescing baseline: 9 == 3 to 5us पूर्णांकerrupt delay per command */
#घोषणा ISCI_COALESCE_BASE 9

/* expander attached sata devices require 3 rnc slots */
अटल अंतरभूत पूर्णांक sci_remote_device_node_count(काष्ठा isci_remote_device *idev)
अणु
	काष्ठा करोमुख्य_device *dev = idev->करोमुख्य_dev;

	अगर (dev_is_sata(dev) && dev->parent)
		वापस SCU_STP_REMOTE_NODE_COUNT;
	वापस SCU_SSP_REMOTE_NODE_COUNT;
पूर्ण

/**
 * sci_controller_clear_invalid_phy() -
 *
 * This macro will clear the bit in the invalid phy mask क्रम this controller
 * object.  This is used to control messages reported क्रम invalid link up
 * notअगरications.
 */
#घोषणा sci_controller_clear_invalid_phy(controller, phy) \
	((controller)->invalid_phy_mask &= ~(1 << (phy)->phy_index))

अटल अंतरभूत काष्ठा device *scirdev_to_dev(काष्ठा isci_remote_device *idev)
अणु
	अगर (!idev || !idev->isci_port || !idev->isci_port->isci_host)
		वापस शून्य;

	वापस &idev->isci_port->isci_host->pdev->dev;
पूर्ण

अटल अंतरभूत bool is_a2(काष्ठा pci_dev *pdev)
अणु
	अगर (pdev->revision < 4)
		वापस true;
	वापस false;
पूर्ण

अटल अंतरभूत bool is_b0(काष्ठा pci_dev *pdev)
अणु
	अगर (pdev->revision == 4)
		वापस true;
	वापस false;
पूर्ण

अटल अंतरभूत bool is_c0(काष्ठा pci_dev *pdev)
अणु
	अगर (pdev->revision == 5)
		वापस true;
	वापस false;
पूर्ण

अटल अंतरभूत bool is_c1(काष्ठा pci_dev *pdev)
अणु
	अगर (pdev->revision >= 6)
		वापस true;
	वापस false;
पूर्ण

क्रमागत cable_selections अणु
	लघु_cable     = 0,
	दीर्घ_cable      = 1,
	medium_cable    = 2,
	undefined_cable = 3
पूर्ण;

#घोषणा CABLE_OVERRIDE_DISABLED (0x10000)

अटल अंतरभूत पूर्णांक is_cable_select_overridden(व्योम)
अणु
	वापस cable_selection_override < CABLE_OVERRIDE_DISABLED;
पूर्ण

क्रमागत cable_selections decode_cable_selection(काष्ठा isci_host *ihost, पूर्णांक phy);
व्योम validate_cable_selections(काष्ठा isci_host *ihost);
अक्षर *lookup_cable_names(क्रमागत cable_selections);

/* set hw control क्रम 'activity', even though active enclosures seem to drive
 * the activity led on their own.  Skip setting FSENG control on 'status' due
 * to unexpected operation and 'error' due to not being a supported स्वतःmatic
 * FSENG output
 */
#घोषणा SGPIO_HW_CONTROL 0x00000443

अटल अंतरभूत पूर्णांक isci_gpio_count(काष्ठा isci_host *ihost)
अणु
	वापस ARRAY_SIZE(ihost->scu_रेजिस्टरs->peg0.sgpio.output_data_select);
पूर्ण

व्योम sci_controller_post_request(काष्ठा isci_host *ihost,
				      u32 request);
व्योम sci_controller_release_frame(काष्ठा isci_host *ihost,
				       u32 frame_index);
व्योम sci_controller_copy_sata_response(व्योम *response_buffer,
					    व्योम *frame_header,
					    व्योम *frame_buffer);
क्रमागत sci_status sci_controller_allocate_remote_node_context(काष्ठा isci_host *ihost,
								 काष्ठा isci_remote_device *idev,
								 u16 *node_id);
व्योम sci_controller_मुक्त_remote_node_context(
	काष्ठा isci_host *ihost,
	काष्ठा isci_remote_device *idev,
	u16 node_id);

काष्ठा isci_request *sci_request_by_tag(काष्ठा isci_host *ihost, u16 io_tag);
व्योम sci_controller_घातer_control_queue_insert(काष्ठा isci_host *ihost,
					       काष्ठा isci_phy *iphy);
व्योम sci_controller_घातer_control_queue_हटाओ(काष्ठा isci_host *ihost,
					       काष्ठा isci_phy *iphy);
व्योम sci_controller_link_up(काष्ठा isci_host *ihost, काष्ठा isci_port *iport,
			    काष्ठा isci_phy *iphy);
व्योम sci_controller_link_करोwn(काष्ठा isci_host *ihost, काष्ठा isci_port *iport,
			      काष्ठा isci_phy *iphy);
व्योम sci_controller_remote_device_stopped(काष्ठा isci_host *ihost,
					  काष्ठा isci_remote_device *idev);

क्रमागत sci_status sci_controller_जारी_io(काष्ठा isci_request *ireq);
पूर्णांक isci_host_scan_finished(काष्ठा Scsi_Host *, अचिन्हित दीर्घ);
व्योम isci_host_start(काष्ठा Scsi_Host *);
u16 isci_alloc_tag(काष्ठा isci_host *ihost);
क्रमागत sci_status isci_मुक्त_tag(काष्ठा isci_host *ihost, u16 io_tag);
व्योम isci_tci_मुक्त(काष्ठा isci_host *ihost, u16 tci);
व्योम ireq_करोne(काष्ठा isci_host *ihost, काष्ठा isci_request *ireq, काष्ठा sas_task *task);

पूर्णांक isci_host_init(काष्ठा isci_host *);
व्योम isci_host_completion_routine(अचिन्हित दीर्घ data);
व्योम isci_host_deinit(काष्ठा isci_host *);
व्योम sci_controller_disable_पूर्णांकerrupts(काष्ठा isci_host *ihost);
bool sci_controller_has_remote_devices_stopping(काष्ठा isci_host *ihost);
व्योम sci_controller_transition_to_पढ़ोy(काष्ठा isci_host *ihost, क्रमागत sci_status status);

क्रमागत sci_status sci_controller_start_io(
	काष्ठा isci_host *ihost,
	काष्ठा isci_remote_device *idev,
	काष्ठा isci_request *ireq);

क्रमागत sci_status sci_controller_start_task(
	काष्ठा isci_host *ihost,
	काष्ठा isci_remote_device *idev,
	काष्ठा isci_request *ireq);

क्रमागत sci_status sci_controller_terminate_request(
	काष्ठा isci_host *ihost,
	काष्ठा isci_remote_device *idev,
	काष्ठा isci_request *ireq);

क्रमागत sci_status sci_controller_complete_io(
	काष्ठा isci_host *ihost,
	काष्ठा isci_remote_device *idev,
	काष्ठा isci_request *ireq);

व्योम sci_port_configuration_agent_स्थिरruct(
	काष्ठा sci_port_configuration_agent *port_agent);

क्रमागत sci_status sci_port_configuration_agent_initialize(
	काष्ठा isci_host *ihost,
	काष्ठा sci_port_configuration_agent *port_agent);

पूर्णांक isci_gpio_ग_लिखो(काष्ठा sas_ha_काष्ठा *, u8 reg_type, u8 reg_index,
		    u8 reg_count, u8 *ग_लिखो_data);
#पूर्ण_अगर

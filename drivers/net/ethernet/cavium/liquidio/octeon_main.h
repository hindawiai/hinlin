<शैली गुरु>
/**********************************************************************
 * Author: Cavium, Inc.
 *
 * Contact: support@cavium.com
 *          Please include "LiquidIO" in the subject.
 *
 * Copyright (c) 2003-2016 Cavium, Inc.
 *
 * This file is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful, but
 * AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or
 * NONINFRINGEMENT.  See the GNU General Public License क्रम more details.
 ***********************************************************************/
/*! \पile octeon_मुख्य.h
 *  \मrief Host Driver: This file is included by all host driver source files
 *  to include common definitions.
 */

#अगर_अघोषित _OCTEON_MAIN_H_
#घोषणा  _OCTEON_MAIN_H_

#समावेश <linux/sched/संकेत.स>

#अगर BITS_PER_LONG == 32
#घोषणा CVM_CAST64(v) ((दीर्घ दीर्घ)(v))
#या_अगर BITS_PER_LONG == 64
#घोषणा CVM_CAST64(v) ((दीर्घ दीर्घ)(दीर्घ)(v))
#अन्यथा
#त्रुटि "Unknown system architecture"
#पूर्ण_अगर

#घोषणा DRV_NAME "LiquidIO"

काष्ठा octeon_device_priv अणु
	/** Tasklet काष्ठाures क्रम this device. */
	काष्ठा tasklet_काष्ठा droq_tasklet;
	अचिन्हित दीर्घ napi_mask;
	काष्ठा octeon_device *dev;
पूर्ण;

/** This काष्ठाure is used by NIC driver to store inक्रमmation required
 * to मुक्त the sk_buff when the packet has been fetched by Octeon.
 * Bytes offset below assume worst-हाल of a 64-bit प्रणाली.
 */
काष्ठा octnet_buf_मुक्त_info अणु
	/** Bytes 1-8.  Poपूर्णांकer to network device निजी काष्ठाure. */
	काष्ठा lio *lio;

	/** Bytes 9-16.  Poपूर्णांकer to sk_buff. */
	काष्ठा sk_buff *skb;

	/** Bytes 17-24.  Poपूर्णांकer to gather list. */
	काष्ठा octnic_gather *g;

	/** Bytes 25-32. Physical address of skb->data or gather list. */
	u64 dptr;

	/** Bytes 33-47. Piggybacked soft command, अगर any */
	काष्ठा octeon_soft_command *sc;
पूर्ण;

/* BQL-related functions */
पूर्णांक octeon_report_sent_bytes_to_bql(व्योम *buf, पूर्णांक reqtype);
व्योम octeon_update_tx_completion_counters(व्योम *buf, पूर्णांक reqtype,
					  अचिन्हित पूर्णांक *pkts_compl,
					  अचिन्हित पूर्णांक *bytes_compl);
व्योम octeon_report_tx_completion_to_bql(व्योम *txq, अचिन्हित पूर्णांक pkts_compl,
					अचिन्हित पूर्णांक bytes_compl);
व्योम octeon_pf_changed_vf_macaddr(काष्ठा octeon_device *oct, u8 *mac);

व्योम octeon_schedule_rxq_oom_work(काष्ठा octeon_device *oct,
				  काष्ठा octeon_droq *droq);

/** Swap 8B blocks */
अटल अंतरभूत व्योम octeon_swap_8B_data(u64 *data, u32 blocks)
अणु
	जबतक (blocks) अणु
		cpu_to_be64s(data);
		blocks--;
		data++;
	पूर्ण
पूर्ण

/**
 * \मrief unmaps a PCI BAR
 * @param oct Poपूर्णांकer to Octeon device
 * @param baridx bar index
 */
अटल अंतरभूत व्योम octeon_unmap_pci_barx(काष्ठा octeon_device *oct, पूर्णांक baridx)
अणु
	dev_dbg(&oct->pci_dev->dev, "Freeing PCI mapped regions for Bar%d\n",
		baridx);

	अगर (oct->mmio[baridx].करोne)
		iounmap(oct->mmio[baridx].hw_addr);

	अगर (oct->mmio[baridx].start)
		pci_release_region(oct->pci_dev, baridx * 2);
पूर्ण

/**
 * \मrief maps a PCI BAR
 * @param oct Poपूर्णांकer to Octeon device
 * @param baridx bar index
 * @param max_map_len maximum length of mapped memory
 */
अटल अंतरभूत पूर्णांक octeon_map_pci_barx(काष्ठा octeon_device *oct,
				      पूर्णांक baridx, पूर्णांक max_map_len)
अणु
	u32 mapped_len = 0;

	अगर (pci_request_region(oct->pci_dev, baridx * 2, DRV_NAME)) अणु
		dev_err(&oct->pci_dev->dev, "pci_request_region failed for bar %d\n",
			baridx);
		वापस 1;
	पूर्ण

	oct->mmio[baridx].start = pci_resource_start(oct->pci_dev, baridx * 2);
	oct->mmio[baridx].len = pci_resource_len(oct->pci_dev, baridx * 2);

	mapped_len = oct->mmio[baridx].len;
	अगर (!mapped_len)
		जाओ err_release_region;

	अगर (max_map_len && (mapped_len > max_map_len))
		mapped_len = max_map_len;

	oct->mmio[baridx].hw_addr =
		ioremap(oct->mmio[baridx].start, mapped_len);
	oct->mmio[baridx].mapped_len = mapped_len;

	dev_dbg(&oct->pci_dev->dev, "BAR%d start: 0x%llx mapped %u of %u bytes\n",
		baridx, oct->mmio[baridx].start, mapped_len,
		oct->mmio[baridx].len);

	अगर (!oct->mmio[baridx].hw_addr) अणु
		dev_err(&oct->pci_dev->dev, "error ioremap for bar %d\n",
			baridx);
		जाओ err_release_region;
	पूर्ण
	oct->mmio[baridx].करोne = 1;

	वापस 0;

err_release_region:
	pci_release_region(oct->pci_dev, baridx * 2);
	वापस 1;
पूर्ण

/* input parameter:
 * sc: poपूर्णांकer to a soft request
 * समयout: milli sec which an application wants to रुको क्रम the
	    response of the request.
 *          0: the request will रुको until its response माला_लो back
 *	       from the firmware within LIO_SC_MAX_TMO_MS milli sec.
 *	       It the response करोes not वापस within
 *	       LIO_SC_MAX_TMO_MS milli sec, lio_process_ordered_list()
 *	       will move the request to zombie response list.
 *
 * वापस value:
 * 0: got the response from firmware क्रम the sc request.
 * त्रुटि_सं -EINTR: user पात the command.
 * त्रुटि_सं -ETIME: user spefअगरied समयout value has been expired.
 * त्रुटि_सं -EBUSY: the response of the request करोes not वापस in
 *               resonable समय (LIO_SC_MAX_TMO_MS).
 *               the sc wll be move to zombie response list by
 *               lio_process_ordered_list()
 *
 * A request with non-zero वापस value, the sc->caller_is_करोne
 *  will be marked 1.
 * When getting a request with zero वापस value, the requestor
 *  should mark sc->caller_is_करोne with 1 after examing the
 *  response of sc.
 * lio_process_ordered_list() will मुक्त the soft command on behalf
 * of the soft command requestor.
 * This is to fix the possible race condition of both समयout process
 * and lio_process_ordered_list()/callback function to मुक्त a
 * sc strucutre.
 */
अटल अंतरभूत पूर्णांक
रुको_क्रम_sc_completion_समयout(काष्ठा octeon_device *oct_dev,
			       काष्ठा octeon_soft_command *sc,
			       अचिन्हित दीर्घ समयout)
अणु
	पूर्णांक त्रुटि_सं = 0;
	दीर्घ समयout_jअगरf;

	अगर (समयout)
		समयout_jअगरf = msecs_to_jअगरfies(समयout);
	अन्यथा
		समयout_jअगरf = MAX_SCHEDULE_TIMEOUT;

	समयout_jअगरf =
		रुको_क्रम_completion_पूर्णांकerruptible_समयout(&sc->complete,
							  समयout_jअगरf);
	अगर (समयout_jअगरf == 0) अणु
		dev_err(&oct_dev->pci_dev->dev, "%s: sc is timeout\n",
			__func__);
		WRITE_ONCE(sc->caller_is_करोne, true);
		त्रुटि_सं = -ETIME;
	पूर्ण अन्यथा अगर (समयout_jअगरf == -ERESTARTSYS) अणु
		dev_err(&oct_dev->pci_dev->dev, "%s: sc is interrupted\n",
			__func__);
		WRITE_ONCE(sc->caller_is_करोne, true);
		त्रुटि_सं = -EINTR;
	पूर्ण अन्यथा  अगर (sc->sc_status == OCTEON_REQUEST_TIMEOUT) अणु
		dev_err(&oct_dev->pci_dev->dev, "%s: sc has fatal timeout\n",
			__func__);
		WRITE_ONCE(sc->caller_is_करोne, true);
		त्रुटि_सं = -EBUSY;
	पूर्ण

	वापस त्रुटि_सं;
पूर्ण

#अगर_अघोषित ROUNDUP4
#घोषणा ROUNDUP4(val) (((val) + 3) & 0xfffffffc)
#पूर्ण_अगर

#अगर_अघोषित ROUNDUP8
#घोषणा ROUNDUP8(val) (((val) + 7) & 0xfffffff8)
#पूर्ण_अगर

#अगर_अघोषित ROUNDUP16
#घोषणा ROUNDUP16(val) (((val) + 15) & 0xfffffff0)
#पूर्ण_अगर

#अगर_अघोषित ROUNDUP128
#घोषणा ROUNDUP128(val) (((val) + 127) & 0xffffff80)
#पूर्ण_अगर

#पूर्ण_अगर /* _OCTEON_MAIN_H_ */

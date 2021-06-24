<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#अगर_अघोषित _HRT_HIVE_TYPES_H
#घोषणा _HRT_HIVE_TYPES_H

#समावेश "version.h"
#समावेश "defs.h"

#अगर_अघोषित HRTCAT3
#घोषणा _HRTCAT3(m, n, o)     m##n##o
#घोषणा HRTCAT3(m, n, o)      _HRTCAT3(m, n, o)
#पूर्ण_अगर

#अगर_अघोषित HRTCAT4
#घोषणा _HRTCAT4(m, n, o, p)     m##n##o##p
#घोषणा HRTCAT4(m, n, o, p)      _HRTCAT4(m, n, o, p)
#पूर्ण_अगर

#अगर_अघोषित HRTMIN
#घोषणा HRTMIN(a, b) (((a) < (b)) ? (a) : (b))
#पूर्ण_अगर

#अगर_अघोषित HRTMAX
#घोषणा HRTMAX(a, b) (((a) > (b)) ? (a) : (b))
#पूर्ण_अगर

/* boolean data type */
प्रकार अचिन्हित पूर्णांक hive_bool;
#घोषणा hive_false 0
#घोषणा hive_true  1

प्रकार अक्षर                 hive_पूर्णांक8;
प्रकार लघु                hive_पूर्णांक16;
प्रकार पूर्णांक                  hive_पूर्णांक32;
प्रकार दीर्घ दीर्घ            hive_पूर्णांक64;

प्रकार अचिन्हित अक्षर        hive_uपूर्णांक8;
प्रकार अचिन्हित लघु       hive_uपूर्णांक16;
प्रकार अचिन्हित पूर्णांक         hive_uपूर्णांक32;
प्रकार अचिन्हित दीर्घ दीर्घ   hive_uपूर्णांक64;

#घोषणा HRT_DATA_WIDTH	  32
#घोषणा HRT_ADDRESS_WIDTH 64
#घोषणा HRT_DATA_BYTES    (HRT_DATA_WIDTH / 8)
#घोषणा HRT_ADDRESS_BYTES (HRT_ADDRESS_WIDTH / 8)
#घोषणा SIZखातापूर्ण_HRT_REG    (HRT_DATA_WIDTH >> 3)

प्रकार hive_uपूर्णांक32 hrt_data;
प्रकार hive_uपूर्णांक64 hrt_address;

/* use 64 bit addresses in simulation, where possible */
प्रकार hive_uपूर्णांक64  hive_sim_address;

/* below is क्रम csim, not क्रम hrt, नाम and move this अन्यथाwhere */

प्रकार अचिन्हित पूर्णांक hive_uपूर्णांक;
प्रकार hive_uपूर्णांक32  hive_address;
प्रकार hive_address hive_slave_address;
प्रकार hive_address hive_mem_address;

/* MMIO devices */
प्रकार hive_uपूर्णांक    hive_mmio_id;
प्रकार hive_mmio_id hive_slave_id;
प्रकार hive_mmio_id hive_port_id;
प्रकार hive_mmio_id hive_master_id;
प्रकार hive_mmio_id hive_mem_id;
प्रकार hive_mmio_id hive_dev_id;
प्रकार hive_mmio_id hive_fअगरo_id;

प्रकार hive_uपूर्णांक      hive_hier_id;
प्रकार hive_hier_id   hive_device_id;
प्रकार hive_device_id hive_proc_id;
प्रकार hive_device_id hive_cell_id;
प्रकार hive_device_id hive_host_id;
प्रकार hive_device_id hive_bus_id;
प्रकार hive_device_id hive_bridge_id;
प्रकार hive_device_id hive_fअगरo_adapter_id;
प्रकार hive_device_id hive_custom_device_id;

प्रकार hive_uपूर्णांक hive_slot_id;
प्रकार hive_uपूर्णांक hive_fu_id;
प्रकार hive_uपूर्णांक hive_reg_file_id;
प्रकार hive_uपूर्णांक hive_reg_id;

/* Streaming devices */
प्रकार hive_uपूर्णांक hive_outport_id;
प्रकार hive_uपूर्णांक hive_inport_id;

प्रकार hive_uपूर्णांक hive_msink_id;

/* HRT specअगरic */
प्रकार अक्षर *hive_program;
प्रकार अक्षर *hive_function;

#पूर्ण_अगर /* _HRT_HIVE_TYPES_H */

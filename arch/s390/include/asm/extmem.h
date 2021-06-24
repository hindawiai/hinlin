<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  definitions क्रम बाह्यal memory segment support
 *  Copyright IBM Corp. 2003
 */

#अगर_अघोषित _ASM_S390X_DCSS_H
#घोषणा _ASM_S390X_DCSS_H
#अगर_अघोषित __ASSEMBLY__

/* possible values क्रम segment type as वापसed by segment_info */
#घोषणा SEG_TYPE_SW 0
#घोषणा SEG_TYPE_EW 1
#घोषणा SEG_TYPE_SR 2
#घोषणा SEG_TYPE_ER 3
#घोषणा SEG_TYPE_SN 4
#घोषणा SEG_TYPE_EN 5
#घोषणा SEG_TYPE_SC 6
#घोषणा SEG_TYPE_EWEN 7

#घोषणा SEGMENT_SHARED 0
#घोषणा SEGMENT_EXCLUSIVE 1

पूर्णांक segment_load (अक्षर *name, पूर्णांक segtype, अचिन्हित दीर्घ *addr, अचिन्हित दीर्घ *length);
व्योम segment_unload(अक्षर *name);
व्योम segment_save(अक्षर *name);
पूर्णांक segment_type (अक्षर* name);
पूर्णांक segment_modअगरy_shared (अक्षर *name, पूर्णांक करो_nonshared);
व्योम segment_warning(पूर्णांक rc, अक्षर *seg_name);

#पूर्ण_अगर
#पूर्ण_अगर

<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  S390 version
 *    Copyright IBM Corp. 1999
 *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com),
 *               Christian Borntraeger (cborntra@de.ibm.com),
 */

#अगर_अघोषित _ASM_S390_CPCMD_H
#घोषणा _ASM_S390_CPCMD_H

/*
 * the lowlevel function क्रम cpcmd
 */
पूर्णांक __cpcmd(स्थिर अक्षर *cmd, अक्षर *response, पूर्णांक rlen, पूर्णांक *response_code);

/*
 * cpcmd is the in-kernel पूर्णांकerface क्रम issuing CP commands
 *
 * cmd:		null-terminated command string, max 240 अक्षरacters
 * response:	response buffer क्रम VM's textual response
 * rlen:	size of the response buffer, cpcmd will not exceed this size
 *		but will cap the output, अगर its too large. Everything that
 *		did not fit पूर्णांकo the buffer will be silently dropped
 * response_code: वापस poपूर्णांकer क्रम VM's error code
 * वापस value: the size of the response. The caller can check अगर the buffer
 *		was large enough by comparing the वापस value and rlen
 * NOTE: If the response buffer is not in real storage, cpcmd can sleep
 */
पूर्णांक cpcmd(स्थिर अक्षर *cmd, अक्षर *response, पूर्णांक rlen, पूर्णांक *response_code);

#पूर्ण_अगर /* _ASM_S390_CPCMD_H */

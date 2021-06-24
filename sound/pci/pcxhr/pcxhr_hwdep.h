<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Driver क्रम Digigram pcxhr compatible soundcards
 *
 * definitions and makros क्रम basic card access
 *
 * Copyright (c) 2004 by Digigram <alsa@digigram.com>
 */

#अगर_अघोषित __SOUND_PCXHR_HWDEP_H
#घोषणा __SOUND_PCXHR_HWDEP_H


/* firmware status codes  */
#घोषणा PCXHR_FIRMWARE_XLX_INT_INDEX   0
#घोषणा PCXHR_FIRMWARE_XLX_COM_INDEX   1
#घोषणा PCXHR_FIRMWARE_DSP_EPRM_INDEX  2
#घोषणा PCXHR_FIRMWARE_DSP_BOOT_INDEX  3
#घोषणा PCXHR_FIRMWARE_DSP_MAIN_INDEX  4
#घोषणा PCXHR_FIRMWARE_खाताS_MAX_INDEX 5


/* exported */
पूर्णांक  pcxhr_setup_firmware(काष्ठा pcxhr_mgr *mgr);
व्योम pcxhr_reset_board(काष्ठा pcxhr_mgr *mgr);

#पूर्ण_अगर /* __SOUND_PCXHR_HWDEP_H */

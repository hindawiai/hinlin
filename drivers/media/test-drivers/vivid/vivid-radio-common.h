<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * vivid-radio-common.h - common radio rx/tx support functions.
 *
 * Copyright 2014 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#अगर_अघोषित _VIVID_RADIO_COMMON_H_
#घोषणा _VIVID_RADIO_COMMON_H_

/* The supported radio frequency ranges in kHz */
#घोषणा FM_FREQ_RANGE_LOW       (64000U * 16U)
#घोषणा FM_FREQ_RANGE_HIGH      (108000U * 16U)
#घोषणा AM_FREQ_RANGE_LOW       (520U * 16U)
#घोषणा AM_FREQ_RANGE_HIGH      (1710U * 16U)
#घोषणा SW_FREQ_RANGE_LOW       (2300U * 16U)
#घोषणा SW_FREQ_RANGE_HIGH      (26100U * 16U)

क्रमागत अणु BAND_FM, BAND_AM, BAND_SW, TOT_BANDS पूर्ण;

बाह्य स्थिर काष्ठा v4l2_frequency_band vivid_radio_bands[TOT_BANDS];

पूर्णांक vivid_radio_g_frequency(काष्ठा file *file, स्थिर अचिन्हित *freq, काष्ठा v4l2_frequency *vf);
पूर्णांक vivid_radio_s_frequency(काष्ठा file *file, अचिन्हित *freq, स्थिर काष्ठा v4l2_frequency *vf);

व्योम vivid_radio_rds_init(काष्ठा vivid_dev *dev);

#पूर्ण_अगर

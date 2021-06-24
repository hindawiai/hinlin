<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * vivid-cec.h - A Virtual Video Test Driver, cec emulation
 *
 * Copyright 2016 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#अगर_घोषित CONFIG_VIDEO_VIVID_CEC
काष्ठा cec_adapter *vivid_cec_alloc_adap(काष्ठा vivid_dev *dev,
					 अचिन्हित पूर्णांक idx,
					 bool is_source);
व्योम vivid_cec_bus_मुक्त_work(काष्ठा vivid_dev *dev);

#अन्यथा

अटल अंतरभूत व्योम vivid_cec_bus_मुक्त_work(काष्ठा vivid_dev *dev)
अणु
पूर्ण

#पूर्ण_अगर

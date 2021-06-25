<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित S390_CMB_H
#घोषणा S390_CMB_H

#समावेश <uapi/यंत्र/cmb.h>

काष्ठा ccw_device;
बाह्य पूर्णांक enable_cmf(काष्ठा ccw_device *cdev);
बाह्य पूर्णांक disable_cmf(काष्ठा ccw_device *cdev);
बाह्य पूर्णांक __disable_cmf(काष्ठा ccw_device *cdev);
बाह्य u64 cmf_पढ़ो(काष्ठा ccw_device *cdev, पूर्णांक index);
बाह्य पूर्णांक cmf_पढ़ोall(काष्ठा ccw_device *cdev, काष्ठा cmbdata *data);

#पूर्ण_अगर /* S390_CMB_H */

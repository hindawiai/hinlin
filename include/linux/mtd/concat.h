<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * MTD device concatenation layer definitions
 *
 * Copyright तऊ 2002      Robert Kaiser <rkaiser@sysgo.de>
 */

#अगर_अघोषित MTD_CONCAT_H
#घोषणा MTD_CONCAT_H


काष्ठा mtd_info *mtd_concat_create(
    काष्ठा mtd_info *subdev[],  /* subdevices to concatenate */
    पूर्णांक num_devs,               /* number of subdevices      */
    स्थिर अक्षर *name);          /* name क्रम the new device   */

व्योम mtd_concat_destroy(काष्ठा mtd_info *mtd);

#पूर्ण_अगर


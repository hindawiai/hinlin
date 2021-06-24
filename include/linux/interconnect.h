<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2018-2019, Linaro Ltd.
 * Author: Georgi Djakov <georgi.djakov@linaro.org>
 */

#अगर_अघोषित __LINUX_INTERCONNECT_H
#घोषणा __LINUX_INTERCONNECT_H

#समावेश <linux/mutex.h>
#समावेश <linux/types.h>

/* macros क्रम converting to icc units */
#घोषणा Bps_to_icc(x)	((x) / 1000)
#घोषणा kBps_to_icc(x)	(x)
#घोषणा MBps_to_icc(x)	((x) * 1000)
#घोषणा GBps_to_icc(x)	((x) * 1000 * 1000)
#घोषणा bps_to_icc(x)	(1)
#घोषणा kbps_to_icc(x)	((x) / 8 + ((x) % 8 ? 1 : 0))
#घोषणा Mbps_to_icc(x)	((x) * 1000 / 8)
#घोषणा Gbps_to_icc(x)	((x) * 1000 * 1000 / 8)

काष्ठा icc_path;
काष्ठा device;

/**
 * काष्ठा icc_bulk_data - Data used क्रम bulk icc operations.
 *
 * @path: reference to the पूर्णांकerconnect path (पूर्णांकernal use)
 * @name: the name from the "interconnect-names" DT property
 * @avg_bw: average bandwidth in icc units
 * @peak_bw: peak bandwidth in icc units
 */
काष्ठा icc_bulk_data अणु
	काष्ठा icc_path	*path;
	स्थिर अक्षर *name;
	u32 avg_bw;
	u32 peak_bw;
पूर्ण;

पूर्णांक __must_check of_icc_bulk_get(काष्ठा device *dev, पूर्णांक num_paths,
				 काष्ठा icc_bulk_data *paths);
व्योम icc_bulk_put(पूर्णांक num_paths, काष्ठा icc_bulk_data *paths);
पूर्णांक icc_bulk_set_bw(पूर्णांक num_paths, स्थिर काष्ठा icc_bulk_data *paths);
पूर्णांक icc_bulk_enable(पूर्णांक num_paths, स्थिर काष्ठा icc_bulk_data *paths);
व्योम icc_bulk_disable(पूर्णांक num_paths, स्थिर काष्ठा icc_bulk_data *paths);

#अगर IS_ENABLED(CONFIG_INTERCONNECT)

काष्ठा icc_path *icc_get(काष्ठा device *dev, स्थिर पूर्णांक src_id,
			 स्थिर पूर्णांक dst_id);
काष्ठा icc_path *of_icc_get(काष्ठा device *dev, स्थिर अक्षर *name);
काष्ठा icc_path *devm_of_icc_get(काष्ठा device *dev, स्थिर अक्षर *name);
काष्ठा icc_path *of_icc_get_by_index(काष्ठा device *dev, पूर्णांक idx);
व्योम icc_put(काष्ठा icc_path *path);
पूर्णांक icc_enable(काष्ठा icc_path *path);
पूर्णांक icc_disable(काष्ठा icc_path *path);
पूर्णांक icc_set_bw(काष्ठा icc_path *path, u32 avg_bw, u32 peak_bw);
व्योम icc_set_tag(काष्ठा icc_path *path, u32 tag);
स्थिर अक्षर *icc_get_name(काष्ठा icc_path *path);

#अन्यथा

अटल अंतरभूत काष्ठा icc_path *icc_get(काष्ठा device *dev, स्थिर पूर्णांक src_id,
				       स्थिर पूर्णांक dst_id)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा icc_path *of_icc_get(काष्ठा device *dev,
					  स्थिर अक्षर *name)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा icc_path *devm_of_icc_get(काष्ठा device *dev,
						स्थिर अक्षर *name)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा icc_path *of_icc_get_by_index(काष्ठा device *dev, पूर्णांक idx)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम icc_put(काष्ठा icc_path *path)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक icc_enable(काष्ठा icc_path *path)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक icc_disable(काष्ठा icc_path *path)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक icc_set_bw(काष्ठा icc_path *path, u32 avg_bw, u32 peak_bw)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम icc_set_tag(काष्ठा icc_path *path, u32 tag)
अणु
पूर्ण

अटल अंतरभूत स्थिर अक्षर *icc_get_name(काष्ठा icc_path *path)
अणु
	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* CONFIG_INTERCONNECT */

#पूर्ण_अगर /* __LINUX_INTERCONNECT_H */

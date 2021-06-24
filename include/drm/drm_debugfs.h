<शैली गुरु>
/*
 * Internal Header क्रम the Direct Rendering Manager
 *
 * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.
 * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, Calअगरornia.
 * Copyright (c) 2009-2010, Code Aurora Forum.
 * All rights reserved.
 *
 * Author: Rickard E. (Rik) Faith <faith@valinux.com>
 * Author: Gareth Hughes <gareth@valinux.com>
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#अगर_अघोषित _DRM_DEBUGFS_H_
#घोषणा _DRM_DEBUGFS_H_

#समावेश <linux/types.h>
#समावेश <linux/seq_file.h>
/**
 * काष्ठा drm_info_list - debugfs info list entry
 *
 * This काष्ठाure represents a debugfs file to be created by the drm
 * core.
 */
काष्ठा drm_info_list अणु
	/** @name: file name */
	स्थिर अक्षर *name;
	/**
	 * @show:
	 *
	 * Show callback. &seq_file->निजी will be set to the &काष्ठा
	 * drm_info_node corresponding to the instance of this info on a given
	 * &काष्ठा drm_minor.
	 */
	पूर्णांक (*show)(काष्ठा seq_file*, व्योम*);
	/** @driver_features: Required driver features क्रम this entry */
	u32 driver_features;
	/** @data: Driver-निजी data, should not be device-specअगरic. */
	व्योम *data;
पूर्ण;

/**
 * काष्ठा drm_info_node - Per-minor debugfs node काष्ठाure
 *
 * This काष्ठाure represents a debugfs file, as an instantiation of a &काष्ठा
 * drm_info_list on a &काष्ठा drm_minor.
 *
 * FIXME:
 *
 * No it करोesn't make a hole lot of sense that we duplicate debugfs entries क्रम
 * both the render and the primary nodes, but that's how this has organically
 * grown. It should probably be fixed, with a compatibility link, अगर needed.
 */
काष्ठा drm_info_node अणु
	/** @minor: &काष्ठा drm_minor क्रम this node. */
	काष्ठा drm_minor *minor;
	/** @info_ent: ढाँचा क्रम this node. */
	स्थिर काष्ठा drm_info_list *info_ent;
	/* निजी: */
	काष्ठा list_head list;
	काष्ठा dentry *dent;
पूर्ण;

#अगर defined(CONFIG_DEBUG_FS)
व्योम drm_debugfs_create_files(स्थिर काष्ठा drm_info_list *files,
			      पूर्णांक count, काष्ठा dentry *root,
			      काष्ठा drm_minor *minor);
पूर्णांक drm_debugfs_हटाओ_files(स्थिर काष्ठा drm_info_list *files,
			     पूर्णांक count, काष्ठा drm_minor *minor);
#अन्यथा
अटल अंतरभूत व्योम drm_debugfs_create_files(स्थिर काष्ठा drm_info_list *files,
					    पूर्णांक count, काष्ठा dentry *root,
					    काष्ठा drm_minor *minor)
अणुपूर्ण

अटल अंतरभूत पूर्णांक drm_debugfs_हटाओ_files(स्थिर काष्ठा drm_info_list *files,
					   पूर्णांक count, काष्ठा drm_minor *minor)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _DRM_DEBUGFS_H_ */

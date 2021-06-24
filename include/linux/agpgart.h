<शैली गुरु>
/*
 * AGPGART module version 0.99
 * Copyright (C) 1999 Jeff Harपंचांगann
 * Copyright (C) 1999 Precision Insight, Inc.
 * Copyright (C) 1999 Xi Graphics, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * JEFF HARTMANN, OR ANY OTHER CONTRIBUTORS BE LIABLE FOR ANY CLAIM, 
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR 
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE 
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */
#अगर_अघोषित _AGP_H
#घोषणा _AGP_H 1

#समावेश <linux/mutex.h>
#समावेश <linux/agp_backend.h>
#समावेश <uapi/linux/agpgart.h>

काष्ठा agp_info अणु
	काष्ठा agp_version version;	/* version of the driver        */
	u32 bridge_id;		/* bridge venकरोr/device         */
	u32 agp_mode;		/* mode info of bridge          */
	अचिन्हित दीर्घ aper_base;/* base of aperture             */
	माप_प्रकार aper_size;	/* size of aperture             */
	माप_प्रकार pg_total;	/* max pages (swap + प्रणाली)    */
	माप_प्रकार pg_प्रणाली;	/* max pages (प्रणाली)           */
	माप_प्रकार pg_used;		/* current pages used           */
पूर्ण;

काष्ठा agp_setup अणु
	u32 agp_mode;		/* mode info of bridge          */
पूर्ण;

/*
 * The "prot" करोwn below needs still a "sleep" flag somehow ...
 */
काष्ठा agp_segment अणु
	off_t pg_start;		/* starting page to populate    */
	माप_प्रकार pg_count;	/* number of pages              */
	पूर्णांक prot;		/* prot flags क्रम mmap          */
पूर्ण;

काष्ठा agp_segment_priv अणु
	off_t pg_start;
	माप_प्रकार pg_count;
	pgprot_t prot;
पूर्ण;

काष्ठा agp_region अणु
	pid_t pid;		/* pid of process               */
	माप_प्रकार seg_count;	/* number of segments           */
	काष्ठा agp_segment *seg_list;
पूर्ण;

काष्ठा agp_allocate अणु
	पूर्णांक key;		/* tag of allocation            */
	माप_प्रकार pg_count;	/* number of pages              */
	u32 type;		/* 0 == normal, other devspec   */
	u32 physical;           /* device specअगरic (some devices  
				 * need a phys address of the     
				 * actual page behind the gatt    
				 * table)                        */
पूर्ण;

काष्ठा agp_bind अणु
	पूर्णांक key;		/* tag of allocation            */
	off_t pg_start;		/* starting page to populate    */
पूर्ण;

काष्ठा agp_unbind अणु
	पूर्णांक key;		/* tag of allocation            */
	u32 priority;		/* priority क्रम paging out      */
पूर्ण;

काष्ठा agp_client अणु
	काष्ठा agp_client *next;
	काष्ठा agp_client *prev;
	pid_t pid;
	पूर्णांक num_segments;
	काष्ठा agp_segment_priv **segments;
पूर्ण;

काष्ठा agp_controller अणु
	काष्ठा agp_controller *next;
	काष्ठा agp_controller *prev;
	pid_t pid;
	पूर्णांक num_clients;
	काष्ठा agp_memory *pool;
	काष्ठा agp_client *clients;
पूर्ण;

#घोषणा AGP_FF_ALLOW_CLIENT		0
#घोषणा AGP_FF_ALLOW_CONTROLLER 	1
#घोषणा AGP_FF_IS_CLIENT		2
#घोषणा AGP_FF_IS_CONTROLLER		3
#घोषणा AGP_FF_IS_VALID 		4

काष्ठा agp_file_निजी अणु
	काष्ठा agp_file_निजी *next;
	काष्ठा agp_file_निजी *prev;
	pid_t my_pid;
	अचिन्हित दीर्घ access_flags;	/* दीर्घ req'd क्रम set_bit --RR */
पूर्ण;

काष्ठा agp_front_data अणु
	काष्ठा mutex agp_mutex;
	काष्ठा agp_controller *current_controller;
	काष्ठा agp_controller *controllers;
	काष्ठा agp_file_निजी *file_priv_list;
	bool used_by_controller;
	bool backend_acquired;
पूर्ण;

#पूर्ण_अगर				/* _AGP_H */

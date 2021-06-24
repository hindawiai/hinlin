<शैली गुरु>
/*
 * arch/um/include/mem_user.h
 *
 * BRIEF MODULE DESCRIPTION
 * user side memory पूर्णांकerface क्रम support IO memory inside user mode linux
 *
 * Copyright (C) 2001 RidgeRun, Inc.
 * Author: RidgeRun, Inc.
 *         Greg Lonnon glonnon@ridgerun.com or info@ridgerun.com
 *
 *  This program is मुक्त software; you can redistribute  it and/or modअगरy it
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 *
 *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS'' AND   ANY  EXPRESS OR IMPLIED
 *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   सूचीECT, INसूचीECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF
 *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  You should have received a copy of the  GNU General Public License aदीर्घ
 *  with this program; अगर not, ग_लिखो  to the Free Software Foundation, Inc.,
 *  675 Mass Ave, Cambridge, MA 02139, USA.
 */

#अगर_अघोषित _MEM_USER_H
#घोषणा _MEM_USER_H

काष्ठा iomem_region अणु
	काष्ठा iomem_region *next;
	अक्षर *driver;
	पूर्णांक fd;
	पूर्णांक size;
	अचिन्हित दीर्घ phys;
	अचिन्हित दीर्घ virt;
पूर्ण;

बाह्य काष्ठा iomem_region *iomem_regions;
बाह्य पूर्णांक iomem_size;

#घोषणा ROUND_4M(n) ((((अचिन्हित दीर्घ) (n)) + (1 << 22)) & ~((1 << 22) - 1))

बाह्य पूर्णांक init_mem_user(व्योम);
बाह्य व्योम setup_memory(व्योम *entry);
बाह्य अचिन्हित दीर्घ find_iomem(अक्षर *driver, अचिन्हित दीर्घ *len_out);
बाह्य व्योम mem_total_pages(अचिन्हित दीर्घ physmem, अचिन्हित दीर्घ iomem,
		     अचिन्हित दीर्घ highmem);
बाह्य अचिन्हित दीर्घ get_vm(अचिन्हित दीर्घ len);
बाह्य व्योम setup_physmem(अचिन्हित दीर्घ start, अचिन्हित दीर्घ usable,
			  अचिन्हित दीर्घ len, अचिन्हित दीर्घ दीर्घ highmem);
बाह्य व्योम add_iomem(अक्षर *name, पूर्णांक fd, अचिन्हित दीर्घ size);
बाह्य अचिन्हित दीर्घ phys_offset(अचिन्हित दीर्घ phys);
बाह्य व्योम map_memory(अचिन्हित दीर्घ virt, अचिन्हित दीर्घ phys,
		       अचिन्हित दीर्घ len, पूर्णांक r, पूर्णांक w, पूर्णांक x);

#पूर्ण_अगर

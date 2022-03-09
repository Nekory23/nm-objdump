##
## EPITECH PROJECT, 2021
## B-PSU-nm_objdump
## File description:
## Makefile
##

NAME_NM	=	my_nm

NAME_OBJDUMP	=	my_objdump

NM 		=	nm/

OBJDUMP	=	objdump/

all	:	nm objdump

nm	:	
		make -C $(NM) -f Makefile -s
		mv $(NM)my_nm ./

objdump	:
		make -C $(OBJDUMP) -f Makefile -s
		mv $(OBJDUMP)my_objdump ./

clean	:
		make clean -C $(NM) -f Makefile -s
		make clean -C $(OBJDUMP) -f Makefile -s

fclean	:	clean
		make fclean -C $(NM) -f Makefile -s
		make fclean -C $(OBJDUMP) -f Makefile -s
		rm -f $(NAME_NM)
		rm -f $(NAME_OBJDUMP)

tests_run:	re
		make tests_run -C $(NM) -f Makefile -s
		make tests_run -C $(OBJDUMP) -f Makefile -s

coverage:
		make coverage -C $(NM) -f Makefile -s
		make coverage -C $(OBJDUMP) -f Makefile -s

re	:	fclean all

.PHONY	:	nm objdump all clean fclean re
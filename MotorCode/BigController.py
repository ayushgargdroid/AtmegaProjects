import pygame
import time

class BigController():
	def __init__(self):
		global joystick
		pygame.init()
		pygame.joystick.init()
		if pygame.joystick.get_init() == 1:
			print("Module initialized")
		joystickinit = pygame.joystick.Joystick(0)
		print "Joystick's name : "+joystickinit.get_name() + " id : "+str(joystickinit.get_id())
		joystickinit.init()
		joystick = joystickinit
		self.main()

	def mapVal(self,a,b,c,d,e):
		return (a-b)*(e-d)/(c-b) + d

	def main(self):
		clock = pygame.time.Clock()
		global joystick 
		print joystick.get_name()

		leftr = leftf = rightr = rightf = x = y = pressed = throttle = rot = 0
		buffVal = 50
		centerBuff = 10
		prevx = prevy = 512

		while(1):
			for event in pygame.event.get():
				if event.type == pygame.JOYAXISMOTION :
					print "yolo"
					

				if event.type == pygame.JOYBUTTONDOWN:
					for button in range(joystick.get_numbuttons()):
						if joystick.get_button(button) is 1:
							pressed = button
					
			x = joystick.get_axis(0)*512.0+512
			y = joystick.get_axis(1)*512.0+512	
			throttle = joystick.get_axis(3)*100.0+100

			#for i in range(1,8):
			#	if throttle <= 25*i:
			#		top = 65535/8 * i
			#		break
			top = self.mapVal(throttle,0,200,0,65535)

			if(x>1023): 
				x = 1023
			if(y>1023): 
				y = 1023
			if(x-prevx>buffVal):
				x = prevx + buffVal
			elif(x-prevx<-buffVal):
				x = prevx - buffVal
			if(y-prevy>buffVal):
				y = prevy + buffVal
			elif(y-prevy<-buffVal):
				y = prevy - buffVal
			if(x<=512+centerBuff and x>=512-centerBuff and y<=512+centerBuff and y>=512-centerBuff):
				leftf = leftr = rightf = rightr = 0
			elif(x<=512+centerBuff and x>=512-centerBuff):
				if(y>=512+centerBuff):
					rightf = self.mapVal(y,512+centerBuff,1023,0,top)
					rightr = 0
					leftr = self.mapVal(y,512+centerBuff,1023,0,top)
					leftf = 0
				elif(y<=512-centerBuff):
					rightr = self.mapVal(y,0,512-centerBuff,top,0)
					rightf = 0
					leftf = self.mapVal(y,0,512-centerBuff,top,0)
					leftr = 0
			elif(y<=512+centerBuff and y>=512-centerBuff):
				if(x>=512+centerBuff):
					leftf = self.mapVal(x,512+centerBuff,1023,0,top)
					leftr = 0
					rightf = self.mapVal(x,512+centerBuff,1023,0,top)
					rightr = 0
				elif(x<512-centerBuff):
					leftr = self.mapVal(x,0,512-centerBuff,top,0)
					leftf = 0
					rightf = 0
					rightr = self.mapVal(x,0,512-centerBuff,top,0)
			else:
				refx = refy = 0
				if(y<512):
					if(x>512):
						refy = y
						refx = 1023 - refy

						if(x<refx):
							leftr = 0
							leftf = self.mapVal(y,0,511,top,0)
							rightf = 0
							rightr = self.mapVal(x,512,refx,top,0)

						else:
							refx = x
							refy = 1023 - refx
							leftr = 0
							leftf = self.mapVal(x,512,1023,0,top)
							rightr = 0
							rightf = self.mapVal(y,refy,511,0,top)

					else:
						refy = refx = y

						if(x>refx):
							rightf = 0
							rightr = self.mapVal(y,0,511,top,0)
							leftr = 0
							leftf = self.mapVal(x,refx,511,0,top)

						else:
							refx = refy = x
							rightf = 0
							rightr = self.mapVal(x,0,511,top,0)
							leftf = 0
							leftr = self.mapVal(y,refy,511,0,top)

				else:
					if(x<512):
						refy = y
						refx = 1023 - refy

						if(x>refx):
							print "!!@@x : "+str(x)+" y : "+str(y)
							leftf = 0
							leftr = self.mapVal(y,512,1023,0,top)
							rightf = self.mapVal(x,refx,511,0,top)
							rightr = 0
							print("leftf : "+str(leftf)+" rightf : "+str(rightf))
							print("leftr : "+str(leftr)+" rightr : "+str(rightr))

						else:
							refx = x
							refy = 1023 - refx
							leftf = 0
							leftr = self.mapVal(y,512,1023,0,top)
							rightr = 0
							rightf = self.mapVal(x,refx,511,0,top)

					else:
						refx = refy = y
						if(x>refx):
							refx = refy = x
							rightr = 0
							rightf = self.mapVal(x,512,1023,0,top)
							leftr = 0
							leftf = self.mapVal(y,512,refy,top,0)

						else:
							refx = refy = y
							rightr = 0
							rightf = self.mapVal(y,512,1023,0,top)
							leftf = 0
							leftr = self.mapVal(x,512,refx,top,0)


			prevx = x
			prevy = y
			print ("x : "+str(x)+" y : "+str(y))			
			print("leftf : "+str(leftf)+" rightf : "+str(rightf))
			print("leftr : "+str(leftr)+" rightr : "+str(rightr))
			print("Throttle : "+str(throttle))
			clock.tick(20)
				
				




BigController()

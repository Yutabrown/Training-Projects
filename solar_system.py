import pygame
import sys
import math

WHITE = (255, 255, 255)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)
BLACK = (0, 0, 0)
FPS_LIMIT = 150
SCREEN_WIDTH = 1223
SCREEN_HEIGHT = 728

class Sun:
    def __init__(self, center_pos) -> None:
        self.size = 20
        self.position = center_pos
        self.speed = 0
        self.color = (255, 255, 0)

    @staticmethod
    def calculate_center_position(rect):
        return (rect.centerx, rect.centery)

    def update_position(self, screen):
        rect = screen.get_rect()
        self.position = (rect.centerx, rect.centery)

class Planet:
    def __init__(self, size, initial_position, speed, color, anchor_radius) -> None:
        self.size = size
        self.position = initial_position
        self.speed = speed
        self.color = color
        self.anchor_radius = anchor_radius
        
    def update_position(self, time_elapsed, sun_position):
        angle = self.speed * time_elapsed
        posx = self.anchor_radius * math.sin(angle) + sun_position[0]
        posy = self.anchor_radius * math.cos(angle) + sun_position[1]
        self.position = (posx, posy)

def draw_sun(screen, sun):
    pygame.draw.circle(screen, sun.color, (int(sun.position[0]), int(sun.position[1])), sun.size)

def draw_planets(screen, planets):
    for planet in planets:
        pygame.draw.circle(screen, planet.color, (int(planet.position[0]), int(planet.position[1])), planet.size)

def render_text(screen, text, position, font_size=24, color=WHITE):
    font = pygame.font.Font(None, font_size)
    text_surface = font.render(text, True, color)
    screen.blit(text_surface, position)

def main():
    pygame.init()

    screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
    center_pos = Sun.calculate_center_position(screen.get_rect())
    sun = Sun(center_pos)

    planets = [
        Planet(5, (300, 250), 0.01, RED, 100),  # Mercury
        Planet(8, (350, 250), 0.008, (255, 255, 0), 150),  # Venus
        Planet(10, (400, 250), 0.006, (0, 255, 0), 200),  # Earth
        Planet(7, (450, 250), 0.005, (255, 0, 0), 250),  # Mars
        Planet(15, (500, 250), 0.004, (255, 150, 0), 300),  # Jupiter
        Planet(12, (550, 250), 0.003, (255, 0, 0), 350),  # Saturn
        Planet(11, (600, 250), 0.001, (0, 0, 255), 400),  # Uranus
        Planet(10, (650, 250), 0.0001, (0, 255, 0), 450),  # Neptune
    ]
    
    clock = pygame.time.Clock()
    
    running, pause = True, False

    while running:
        time_elapsed = clock.tick(FPS_LIMIT) / 1000.0

        for e in pygame.event.get():
            if e.type == pygame.QUIT:
                running = False
            elif e.type == pygame.KEYDOWN:
                if e.key == pygame.K_SPACE:
                    pause = not pause

        screen.fill(BLACK)

        sun.update_position(screen)
        draw_sun(screen, sun)

        if not pause:
            for planet in planets:
                planet.update_position(pygame.time.get_ticks(), sun.position)

        draw_planets(screen, planets)

        render_text(screen, "Solar System Simulation", (10, 10))
        if pause:
            render_text(screen, "Paused", (SCREEN_WIDTH // 2 - 50, SCREEN_HEIGHT // 2 - 12), font_size=48)

        pygame.display.flip()

    pygame.quit()

if __name__ == "__main__":
    main()
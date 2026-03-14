import tkinter as tk
from tkinter import messagebox, Toplevel, Label
from PIL import Image, ImageTk
import tkinter.font as tkFont

# ==== Data dictionaries with prices and image paths ====

clothes_items = {
    "Hoddies": {"price": 999, "img": r"c:/Users/rimsha/Downloads/Hoddies.jpeg"},
    "Lehengas": {"price": 1000, "img": r"c:/Users/rimsha/Downloads/Lehengas.jpeg"},
    "Plazo suits": {"price": 1199, "img": r"c:/Users/rimsha/Downloads/Plazo suits.jpeg"},
    "Sarees": {"price": 1500, "img": r"c:/Users/rimsha/Downloads/Sarees.jpeg"},
    "Garara": {"price": 1499, "img": r"c:/Users/rimsha/Downloads/Garara.jpeg"}
}

shoes_items = {
    "Nike": {"price": 600, "img": r"c:/Users/rimsha/Downloads/nike.jpeg"},
    "Adidas": {"price": 250, "img": r"c:/Users/rimsha/Downloads/adidas.jpeg"},
    "Puma": {"price": 1200, "img": r"c:/Users/rimsha/Downloads/Puma.jpeg"},
    "Reebok": {"price": 1200, "img": r"c:/Users/rimsha/Downloads/Reebok.jpeg"}
}

Acessories_items = {
    "Chains": {"price": 1000, "img": r"c:/Users/rimsha/Downloads/chain.jpeg"},
    "rings": {"price": 1000, "img": r"c:/Users/rimsha/Downloads/rings.jpeg"},
    "earings": {"price": 1000, "img": r"c:/Users/rimsha/Downloads/earings.jpeg"},
    "bracelets": {"price": 1000, "img": r"c:/Users/rimsha/Downloads/Bracelets.jpg"}
}

skincare_items = {
    "Biotique": {"price": 600, "img": r"c:/Users/rimsha/Downloads/Biotique.jpeg"},
    "wow": {"price": 1000, "img": r"c:/Users/rimsha/Downloads/wow.jpeg"},
    "lakme": {"price": 1000, "img": r"c:/Users/rimsha/Downloads/Lakme.jpeg"},
    "mama earth": {"price": 1000, "img": r"c:/Users/rimsha/Downloads/mamaearth.jpeg"}
}

# List to keep image references alive
opened_images = []

# ==== Function to open image in new popup window ====

def open_image_window(item_name, img_path):
    win = Toplevel(root)
    win.title(item_name)
    win.config(bg="#ffe6f0")  # Light pink background for popup
    try:
        img = Image.open(img_path)
        img = img.resize((600, 450))  # Resize to fit nicely
        photo = ImageTk.PhotoImage(img)
        opened_images.append(photo)  # Keep reference
        label = Label(win, image=photo, bg="#ffe6f0")
        label.pack(padx=10, pady=10)
    except Exception as e:
        messagebox.showerror("Image Error", f"Could not open image for {item_name}.\n{e}")

# ==== Function to display affordable items based on budget ====

def display_affordable():
    fashion_type = fashion_var.get()
    budget_str = budget_entry.get().strip()

    try:
        budget = float(budget_str)
    except ValueError:
        messagebox.showerror("Invalid input", "Please enter a valid number for budget.")
        return

    if fashion_type == "clothes":
        items = clothes_items
    elif fashion_type == "shoes":
        items = shoes_items
    elif fashion_type == "Acessories":
        items = Acessories_items
    elif fashion_type == "skincare":
        items = skincare_items
    else:
        messagebox.showerror("Invalid input", "Please select a fashion type.")
        return

    affordable = [item for item, data in items.items() if data["price"] <= budget]

    if affordable:
        result_text = f"With your budget Rs:{budget}, you can afford:\n"
        for item in affordable:
            result_text += f"• {item} (Rs:{items[item]['price']})\n"
        result_label.config(text=result_text, fg="#4b0082")  # Dark purple text

        # Open images for affordable items
        for item in affordable:
            open_image_window(item, items[item]["img"])

    else:
        result_label.config(text="Sorry, no items fit within your budget.", fg="red")

# ==== GUI setup ====

root = tk.Tk()
root.title("Classy - Fashion Budget Checker")
root.geometry("720x700")
root.config(bg="#f7f0f5")  # Soft lavender background

# Title label with font and color
title_font = tkFont.Font(family="Helvetica", size=24, weight="bold")
title_label = tk.Label(root, text="Classy Cart", font=title_font, bg="#f7f0f5", fg="#ff4081")
title_label.pack(pady=20)

# Top image/logo
image = Image.open(r"c:/Users/rimsha")
image = image.resize((180, 180))
gfg = ImageTk.PhotoImage(image)
label_image = tk.Label(root, image=gfg, bg="#f7f0f5")
label_image.pack()

# Frame for inputs with white background and border
form_frame = tk.Frame(root, bg="#ffffff", bd=3, relief="ridge")
form_frame.pack(pady=30, padx=40, fill="x")

# Fashion type label
label_fashion = tk.Label(form_frame, text="Select Fashion Type:", font=("Arial", 14, "bold"), bg="#ffffff", fg="#d81b60")
label_fashion.pack(anchor="w", pady=(10, 5), padx=10)

# Fashion type radio buttons
fashion_var = tk.StringVar(value="clothes")
rb_frame = tk.Frame(form_frame, bg="#ffffff")
rb_frame.pack(anchor="w", padx=20)

colors = {
    "clothes": "#f48fb1",
    "shoes": "#ce93d8",
    "Acessories": "#80deea",
    "skincare": "#a5d6a7"
}

def make_rb(text, val):
    rb = tk.Radiobutton(
        rb_frame,
        text=text,
        variable=fashion_var,
        value=val,
        bg=colors[val],
        fg="black",
        font=("Helvetica", 12, "bold"),
        activebackground=colors[val],
        indicatoron=0,
        width=12,
        pady=5,
    )
    rb.pack(side="left", padx=5, pady=5)

make_rb("Clothes", "clothes")
make_rb("Shoes", "shoes")
make_rb("Accessories", "Acessories")
make_rb("Skincare", "skincare")

# Budget label and entry
label_budget = tk.Label(form_frame, text="Enter your budget (Rs):", font=("Arial", 14, "bold"), bg="#ffffff", fg="#d81b60")
label_budget.pack(anchor="w", pady=(20, 5), padx=10)

budget_entry = tk.Entry(form_frame, font=("Helvetica", 14), bd=3, relief="groove", width=20)
budget_entry.pack(anchor="w", padx=20)

# Button to check affordable items
check_button = tk.Button(
    root,
    text="Check Affordable Items",
    font=("Arial", 14, "bold"),
    bg="#f50057",
    fg="white",
    padx=15,
    pady=8,
    activebackground="#ad1457",
    command=display_affordable,
)
check_button.pack(pady=30)

# Result label to show output
result_label = tk.Label(root, text="", font=("Arial", 14, "bold"), bg="#f7f0f5", justify="left")
result_label.pack(fill="x", padx=40)

root.mainloop()
